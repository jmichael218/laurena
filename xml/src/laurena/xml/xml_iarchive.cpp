///
/// \file     xml_iarchive.cpp
/// \brief    Class for a XML input archive i.e a class to create/fill a class instance from a XML file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a XML input archive i.e a class to create/fill a class instance from a XML file format.
///

#include <laurena/xml/xml_iarchive.hpp>
#include <laurena/xml/xml_language.hpp>

using namespace laurena;
using namespace xml;

iarchive_xml::iarchive_xml() : iarchive()
{
}
iarchive_xml::~iarchive_xml()
{
}

void iarchive_xml::skipTabs()
{
token tk;

    while (true)
    {
        int32 res = this->_tokenizer.readExpected(tk,XML::units(), XML::mask_tab_tokens());

        if (res == -1)
            return;
        
        if (res == XML::TOKEN_COMMENT_START)
        {
            this->_tokenizer.skipUntil("-->",true);
            continue;
        }
    }
}

void iarchive_xml::readToken(token& tk, boost::dynamic_bitset<>& allowed_tokens)
{
    while (true)
    {
        int32 res = this->_tokenizer.readExpected(tk,XML::units(),allowed_tokens);

        if (res == -1)
        {
            std::ostringstream stream;
            this->_tokenizer.prefixErrorMessage(stream);
            stream << " syntax error." ;
            stream.flush();
            std::string msg = stream.str();
            throw LAURENA_FAILED_PARSING_EXCEPTION(msg.c_str(),this->_tokenizer._ptr) ;  
        }

        tk._token_id = res;

        if ( !XML::mask_tab_tokens().test (res))
            return;
        
        if (res == XML::TOKEN_COMMENT_START)
        {
            this->_tokenizer.skipUntil("-->",true);
            continue;
        }
    }
}

void iarchive_xml::readExpected(token& token, word8 tokenId)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(XML::TOKEN_MAX);
    allowed |= XML::mask_tab_tokens();
    allowed.set(tokenId);

    this->readToken(token,allowed);
}

void iarchive_xml::readExpected(token& token, word8 tokenId1, word8 tokenId2)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(XML::TOKEN_MAX);
    allowed |= XML::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);

    this->readToken(token,allowed);
}

void iarchive_xml::readExpected(token& token, word8 tokenId1, word8 tokenId2, word8 tokenId3)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(XML::TOKEN_MAX);
    allowed |= XML::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);
	allowed.set(tokenId3);

    this->readToken(token,allowed);
}

void iarchive_xml::readExpected(token& token, word8 tokenId1, word8 tokenId2, word8 tokenId3, word8 tokenId4)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(XML::TOKEN_MAX);
    allowed |= XML::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);
	allowed.set(tokenId3);
	allowed.set(tokenId4);

    this->readToken(token,allowed);
}


 void iarchive_xml::readAttributes(any& object)
 {

 }

 void iarchive_xml::readEndOfField(const field& f, const std::string& expectedName, any& object)
 {
token t;

    this->readExpected(t,XML::TOKEN_INFERIOR_SLASH);
    this->readExpected(t, XML::TOKEN_KEYWORD);
    std::string keyword = anycast<std::string>(t);

    if (keyword != expectedName)
    {
        std::ostringstream ss;
        ss << "Was expecting </" << expectedName << "> but found </" << keyword << ">.";
        throw LAURENA_FAILED_PARSING_EXCEPTION(ss.str().c_str(),this->_tokenizer._ptr);
    }

    this->readExpected(t, XML::TOKEN_SUPERIOR);

 }

 //! Read value of a class field
 void iarchive_xml::readField (const field& f, const std::string& fieldName, any& object)
 {
const descriptor& fd = f.desc();
token t;
any a;
const class_feature* ft;

    bool isAtomic               = f.desc().has(descriptor::Flags::ATOMIC);
    const format* fieldFormat	= dynamic_cast<const format*>(f.annotations().get(XML::ANNOTATION_NAME, ANNOTATION_FORMAT_ALL));

    // READ ATTRIBUTES
    this->readAttributes(object);

    // End of section
    this->readExpected(t,XML::TOKEN_SLASH_SUPERIOR, XML::TOKEN_SUPERIOR);

    if (t._token_id == XML::TOKEN_SLASH_SUPERIOR)
        return;

	if ( fieldFormat )
    {
	    if (isAtomic)
		{
			fieldFormat->read(this->_tokenizer,a,true);
			f.set(object, a);
		}
		else
			fieldFormat->read(this->_tokenizer,f.get(object, a),true);

        this->readEndOfField(f, fieldName, object);
		return;
	}
 }

void iarchive_xml::readObject(const std::string& tag, any& object)
{
token t;
std::string keyword;
const descriptor* d = object.desc();

    // READ ATTRIBUTES
    this->readAttributes(object);

    // End of section
    this->readExpected(t,XML::TOKEN_INFERIOR_SLASH, XML::TOKEN_SUPERIOR);

    while(true)
    {
        std::string content = this->_tokenizer.readUntil("<",true);
        if (*this->_tokenizer._ptr == '/')
        {
            // Check that incoming keyword is same than the last one
            this->readExpected(t, XML::TOKEN_SLASH);
            this->readExpected(t, XML::TOKEN_KEYWORD);

            std::string keyword = anycast<std::string>(t);
            if (keyword == tag)
            {
                this->readExpected(t, XML::TOKEN_SUPERIOR);
                object.desc()->stoa(content, object);
                return;
            }
            else
            {
                std::ostringstream ss;
                ss << "Was expecting </" << tag << "> but found </" << keyword << ">.";
                throw LAURENA_FAILED_PARSING_EXCEPTION(ss.str().c_str(),this->_tokenizer._ptr);
            }
        }
        else
        {
            // check content is tabs
            if (!const_charsets<>::TABS.validate(content))
            {
                throw LAURENA_FAILED_PARSING_EXCEPTION("Syntax error",this->_tokenizer._ptr);
            }

            // read keyword
            this->readExpected(t, XML::TOKEN_KEYWORD);
            std::string keyword = anycast<std::string>(t);

            // Identification of keyword
	        if (d->has(descriptor::Flags::FIELDS))
	        {
		        const field* f = d->findField(keyword); 
                if (f)
                {
                    this->readField(*f, keyword, object);
                    continue;
                }
            }
            
            std::ostringstream ss;
            ss << keyword << " : unknow child for class " << d->name();
            throw LAURENA_FAILED_PARSING_EXCEPTION(ss.str().c_str(),this->_tokenizer._ptr);
            
        }

    }
}

any& iarchive_xml::parse   ( const std::string& name, any& object)
{

const descriptor& descriptor = *object.desc();
token t;
std::string keyword;

    if (_logger) 
        *_logger << "[ArchiveXML::extract] type='" << name << ", class='" 
              << descriptor.name() << ")." 
                    << std::endl ;

    //<! First keyword found in the file
    this->readExpected(t,XML::TOKEN_INFERIOR);
    this->readExpected(t,XML::TOKEN_KEYWORD);
    _last_keyword = name ;
    keyword = anycast<std::string>(t);
    
    //<! Check than keyword matches
    if (!boost::iequals(name,keyword))        
    {
        std::ostringstream stream;
        this->_tokenizer.prefixErrorMessage(stream);
        stream << " was expecting keyword'" << name << "' but found '" << keyword << "'." ;
        std::string msg = stream.str();
        throw LAURENA_FAILED_PARSING_EXCEPTION(msg.c_str(),this->_tokenizer._ptr) ;  
    }        
    
    this->readObject(name, object);  
    return object;
}

any& iarchive_xml::load (const std::string& filename, const std::string& name, 
                       any& object)
{

    iarchive_xml arc ;
    arc._source_filename = filename;
    arc._tokenizer.load(filename);

    try 
    {
        return  arc.parse(name,object) ;
    }
    catch (const exception& e)
    {        
        std::ostringstream message ;
        (arc._tokenizer.prefixErrorMessage(message)) << e.message ();
        throw LAURENA_FAILED_PARSING_EXCEPTION(message.str().c_str(),arc._tokenizer._ptr) ;      
    }
}

any& iarchive_xml::fromString (const char* source, const std::string& name, 
                       any& object)
{
    iarchive_xml arc ;
    arc._tokenizer.str(source);

    try 
    {
        return arc.parse(name,object) ;
    }
    catch (const exception& e)
    {        
        std::ostringstream message ;
        (arc._tokenizer.prefixErrorMessage(message)) << e.message ();
        throw LAURENA_FAILED_PARSING_EXCEPTION( message.str().c_str(),arc._tokenizer._ptr) ;      
    }    
}
//end of file
