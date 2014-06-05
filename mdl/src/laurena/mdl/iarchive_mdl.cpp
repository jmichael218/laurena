///
/// \file     iarchive_mdl.cpp
/// \brief    Class for a MDL input archive i.e a class to serialize a class from a MDL file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a MDL input archive i.e a class to serialize a class from a MDL file format.
///

#include <laurena/mdl/iarchive_mdl.hpp>
#include <laurena/mdl/mdl_language.hpp>
#include <laurena/algorithm/strings/iequals.hpp>
#include <laurena/algorithm/strings/tolower.hpp>

using namespace laurena;
using namespace mdl;

iarchive_mdl::iarchive_mdl() : iarchive(), _included(false), _depth(0)
{
}
iarchive_mdl::~iarchive_mdl()
{
}

/********************************************************************************/ 
/*          virtual functions impl from iarchive                                */ 
/********************************************************************************/ 
const class language& iarchive_mdl::language() const
{
return MDL::language();
}



void iarchive_mdl::readDirective (const descriptor& descriptor, any& object )
{
token tk;
std::string keyword;

    /****************************************************************************/ 
    /*              read directive keyword                                      */ 
    /****************************************************************************/ 
    tk = std::move (this->read_token(MDL::TOKEN_KEYWORD));
    keyword = anycast<std::string>(tk);
    tolower(keyword);

    if ( keyword == "include" )
    {
        tk = std::move(this->read_token(MDL::TOKEN_SINGLE_STRING));
        std::string str = anycast<std::string>(tk);

        std::string data_directory;
        Filename::extractDirectory(this->_tokenizer._location.filename(),data_directory);

        std::string filename;
        filename.append (data_directory).append("/").append(str);

        iarchive_mdl amdl ;
        amdl._source_filename = filename;
        amdl._tokenizer.load(filename);
        amdl._included = true;

        amdl.readObjectContent(descriptor, object);
        //iarchive_mdl::load(filename.c_str(),_last_keyword,object) ;
    }
    else
    {
        std::ostringstream stream;
        this->_tokenizer.prefixErrorMessage(stream);
        stream << " ," << keyword << " is an unknow directive.";
        stream.flush();
        std::string msg = stream.str();
        throw LAURENA_FAILED_PARSING_EXCEPTION(msg.c_str(),this->_tokenizer._ptr) ;      
    }
}



void iarchive_mdl::readField(const field& f, any& object)
{
const descriptor& fd = f.desc();
token t;
any a;
const class_feature* ft;

    if (this->read_custom_field_format(f, object))
        return; 

    
    if (f.no_quote() || fd.has(descriptor::Flags::NUMERIC_VALUE))
		t = this->read_token(MDL::TOKEN_INTEGER,MDL::TOKEN_KEYWORD);
    else if ((ft = fd.feature(Feature::ANY)))
    {
        const any_feature* acf = dynamic_cast<const any_feature*>(ft);
 
        token classname;
        this->read_token(MDL::TOKEN_PARENTHESIS_OPEN);
        classname = this->read_token(MDL::TOKEN_KEYWORD);
        this->read_token(MDL::TOKEN_PARENTHESIS_CLOSE);

        std::string sclassname = anycast<std::string>(classname);
        const descriptor* anyContentDescriptor = classes::by_name(sclassname);
        if (!anyContentDescriptor)
        {
	        std::ostringstream message;
            (this->_tokenizer.prefixErrorMessage(message)) << " ," << sclassname << " is an unknow class/type.";
            throw LAURENA_FAILED_PARSING_EXCEPTION(message.str().c_str(),this->_tokenizer._ptr) ;  
        }
        if (anyContentDescriptor->has(descriptor::Flags::FIELDS))
        {
            assert(false);
        }
        else
        {
            t = std::move (this->read_token(MDL::TOKEN_INTEGER,MDL::TOKEN_HEXADECIMAL,MDL::TOKEN_STRING));
            t = std::move(anyContentDescriptor->cast(t));
        }
    }
    else
    {
        t = std::move (this->read_token(MDL::TOKEN_INTEGER,MDL::TOKEN_HEXADECIMAL,MDL::TOKEN_STRING));
    }
    
    f.set(object,t);
}

void iarchive_mdl::readElement (const container_feature* cf, const std::string& keyname, any& object)
{
const descriptor* keyDescriptor = cf->keyDescriptor();
any key;
token t;

        const keymapper_feature* mapper = dynamic_cast<const keymapper_feature*>(cf->desc().feature(Feature::KEY_MAPPER));
        if (mapper) 
        {
            any akeyname = keyname;       
            if ( !mapper->find(object,key,akeyname))
            {
	            std::ostringstream stream;
                (this->_tokenizer.prefixErrorMessage(stream)) << " ," << keyname << " is an unknow mappable key.";
                throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ;   
            }		
        }
		else
			if (cf->hasKey())
				keyDescriptor->stoa(keyname, key);

	    t = std::move (this->read_token(MDL::TOKEN_INTEGER,MDL::TOKEN_HEXADECIMAL,MDL::TOKEN_STRING));

		if (cf->hasKey())
		{
			
			cf->set(object,keyDescriptor->cast(key),t);
		}
		else
		{
			cf->push(object, t);
		}
		return ;
}

void iarchive_mdl::readAttribute (const descriptor& d, any& object,const std::string& attribute)
{
token t;
const container_feature* ccf = dynamic_cast<const container_feature*>(d.feature(Feature::CONTAINER));
bool doNotSet = false;

    /****************************************************************************/
    /*              Log parameter                                               */ 
    /****************************************************************************/
    if (_logger)  
            *_logger << "[ArchiveMDL::readAttribute] attribute='" << attribute 
                    << ", class='" << d.name () << ")."                 
                    << std::endl ;

	if (d.has(descriptor::Flags::FIELDS))
	{
		const field* f = d.findField(attribute);    
		if (f)
		{
            this->readField(*f,object);
			this->read_token(MDL::TOKEN_SEMICOLON);
			return ;
		}
	}
	if (ccf)
	{
		this->readElement(ccf,attribute,object);
		this->read_token(MDL::TOKEN_SEMICOLON);
        return;
	}
	
	std::ostringstream stream;
    (this->_tokenizer.prefixErrorMessage(stream))  << " ," << attribute << " is an unknow field/element.";
    throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ;    	

}

void iarchive_mdl::readInjection(const descriptor& d, any& object, const std::string& attribute)
{
token t;
std::string classname;
const descriptor* cd;
any newO;
const container_feature* ccf = dynamic_cast<const container_feature*>(d.feature(Feature::CONTAINER));

    this->read_token(MDL::TOKEN_NEW);
    t = std::move (this->read_token(MDL::TOKEN_KEYWORD));    
    classname = anycast<std::string>(t);

    cd = classes::by_name(classname);
    if (!cd)
    {
       std::ostringstream stream;
       (this->_tokenizer.prefixErrorMessage(stream)) << " Class '" << classname << "' doesn't exist.";
       throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ; 
    }
    this->read_token(MDL::TOKEN_DPOINTS);

    newO = std::move(cd->create());
    std::string keyword ;
    keyword = this->_last_keyword ;
    _last_keyword = classname;
    this->readChildObject(*cd,newO,true);
    _last_keyword = keyword;

    const field* f = d.findField(attribute);
	if (f)
		f->set(object,newO);
	else if (ccf)
	{
        if ( ccf->hasKey())
        {
		    any key;
		    key = ccf->keyDescriptor()->cast(attribute);
            ccf->set(object, key, newO);
        }
        else
        {
            ccf->push(object,newO);
        }
	} 
	else
	{
		std::ostringstream stream;
		(this->_tokenizer.prefixErrorMessage(stream)) << " ," << d.name() << " doesn't have neither fields nor element key with tag '" << attribute << "'" ;
		throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ;  
	}
}

void iarchive_mdl::readObjectContent (const descriptor& d, any& object )
{
token tk;
std::string keyword, safe_keyword;

    this->_depth ++;
    
    /****************************************************************************/
    /*              Log parameter                                               */ 
    /****************************************************************************/
    if (_logger)  
            *_logger << "[ArchiveMDL::readObjectContent] class='" << d.name ()             
                    << std::endl ;
    while ( true )
    {        
        this->skip_tabs();
        if (this->_included && !*this->_tokenizer._ptr && this->_depth ==1)
            return;

		tk = std::move (this->read_token(MDL::TOKEN_AT,MDL::TOKEN_BRACKET_CLOSE,MDL::TOKEN_PRIMARY_KEY, MDL::TOKEN_INTEGER));

        switch (tk._token_id)
        {
            case MDL::TOKEN_AT:
                this->readDirective(d,object);
                continue;

            case MDL::TOKEN_BRACKET_CLOSE:
                this->_depth --;
                return;

			case MDL::TOKEN_INTEGER:
            case MDL::TOKEN_PRIMARY_KEY:
                keyword = anycast<std::string>(tk);
                tk = std::move(this->read_token(MDL::TOKEN_EQUAL, MDL::TOKEN_DPOINTS, MDL::TOKEN_INJECTION));
                switch (tk._token_id)
                {
                    case MDL::TOKEN_DPOINTS:
                       safe_keyword = this->_last_keyword;
                        this->_last_keyword = keyword;
                       this->readChildObject(d,object,false);
                       this->_last_keyword = safe_keyword;                      
                        continue;

                    case MDL::TOKEN_EQUAL:
 
                        this->readAttribute(d,object,keyword);
                        continue;

                    case MDL::TOKEN_INJECTION:                        
                        this->readInjection(d,object,keyword);
                        continue;                                                

                }
        }       
    }
}

void iarchive_mdl::readChildObject (const descriptor& d, any& parent , bool obj_is_parent )
{
any obj;
token tk;
std::string primary;
const descriptor* descriptorObj;
const container_feature* ccf = dynamic_cast<const container_feature*>(d.feature(Feature::CONTAINER));
bool doListPush = false;
    
    /****************************************************************************/
    /*              Log parameter                                               */ 
    /****************************************************************************/
    if (_logger)  
        *_logger << "[IArchiveMDL::readChildObject] _last_keyword='" << _last_keyword
                    << "', obj_is_parent=" << (obj_is_parent?"TRUE":"FALSE")
                    << ", class='" << d.name () << ")." 
                    << std::endl ;

    /****************************************************************************/ 
    /*              Create new object                                           */ 
    /****************************************************************************/   
    if ( obj_is_parent )
    {
        obj = parent ;
        descriptorObj = &d;
    }
    else
    {
        const field* ff = d.findField(this->_last_keyword);
        if (ff)
        {           
            ff->get(parent,obj);
        }
        else
        {
            if ( ccf != NULL)
            {            
                any key = this->_last_keyword;

                if ( ccf->hasKey ())
                {
                    key = std::move(ccf->keyDescriptor()->cast(key));
                    ccf->get(parent,key,obj);    
                } 
                else
                {
                    if ( ccf->elementDescriptor()->name() != this->_last_keyword )
                    {
                        std::ostringstream stream;
                        (this->_tokenizer.prefixErrorMessage(stream)) << " ," << " container without key only accept their element class name as keywords. Was here expecting '" << ccf->elementDescriptor()->name() << "'." ;
                        throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ; 
                    }
                    ccf->elementDescriptor()->clear(obj); 
                    doListPush = true;                                       
                }
            }
        }
        if (obj.empty())
        {
            const field& f = d.getField(this->_last_keyword);
            f.get(parent,obj);
            assert(false);
        }
        descriptorObj = obj.desc();
        

        
        /*
        if (field.isPointer())
        {
            word8** w = (word8**) field.ptr(parent);
            obj = (void*) * w;
        }
        else
            obj = field.ptr(parent);
        */ 
    }

    /****************************************************************************/ 
    /*              Get Idname                                                  */ 
    /****************************************************************************/ 
    std::string idname ;

    tk = std::move ( this->read_token(MDL::TOKEN_PRIMARY_KEY,MDL::TOKEN_NULLKEYWORD,MDL::TOKEN_INTEGER));

    switch (tk._token_id)
    {
        case MDL::TOKEN_NULLKEYWORD:
            break;

        case MDL::TOKEN_PRIMARY_KEY:
        case MDL::TOKEN_INTEGER:   
            if (descriptorObj->has(descriptor::Flags::PRIMARY_KEY)) 
            {
                descriptorObj->primaryKey().set(obj, tk);      
            } else
            {
                std::ostringstream stream;
                (this->_tokenizer.prefixErrorMessage(stream)) << " ," << "class " << descriptorObj->name() << " doesn't have a primary key.";
                throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ;   
            }

            break;
        default:
            assert(false);
            break;
    }


    //  Parse the '{ symbol
    this->read_token(MDL::TOKEN_BRACKET_OPEN);

    // parse object content

    this->readObjectContent (*descriptorObj,obj);

    if (doListPush && ccf) 
    {
        ccf->push(parent,obj);
    }


}

any& iarchive_mdl::parse   ( const std::string& name, any& object)
{
const descriptor& descriptor = *object.desc();
token t;
std::string keyword;

    if (_logger) 
        *_logger << "[ArchiveMDL::extract] type='" << name << ", class='" 
              << descriptor.name() << ")." 
                    << std::endl ;

    //<! First keyword found in the file
    t = std::move ( this->read_token(MDL::TOKEN_KEYWORD));
    _last_keyword = name ;
    keyword = anycast<std::string>(t);
    
    //<! Check than keyword matches
    if (!iequals(name,keyword))        
    {
        std::ostringstream stream;
        this->_tokenizer.prefixErrorMessage(stream);
        stream << " was expecting keyword'" << name << "' but found '" << keyword << "'." ;
        std::string msg = stream.str();
        throw LAURENA_FAILED_PARSING_EXCEPTION(msg.c_str(),this->_tokenizer._ptr) ;  
    }        

    // read the ':' after an object Type 
    this->read_token(MDL::TOKEN_DPOINTS);   

    this->readChildObject(descriptor,object , true ) ;

    return object;
}

any& iarchive_mdl::load (const std::string& filename, const std::string& name, 
                       any& object)
{

    iarchive_mdl amdl ;
    amdl._source_filename = filename;
    amdl._tokenizer.load(filename);

    try 
    {
        return  amdl.parse(name,object) ;
    }
    catch (const exception& e)
    {        
        std::ostringstream message ;
        (amdl._tokenizer.prefixErrorMessage(message)) << e.message ();
        throw LAURENA_FAILED_PARSING_EXCEPTION(message.str().c_str(),amdl._tokenizer._ptr) ;      
    }
}

any& iarchive_mdl::fromString (const char* source, const std::string& name, 
                       any& object)
{
    iarchive_mdl amdl ;
    amdl._tokenizer.str(source);

    try 
    {
        return amdl.parse(name,object) ;
    }
    catch (const exception& e)
    {        
        std::ostringstream message ;
        (amdl._tokenizer.prefixErrorMessage(message)) << e.message ();
        throw LAURENA_FAILED_PARSING_EXCEPTION( message.str().c_str(),amdl._tokenizer._ptr) ;      
    }    
}
//end of file
