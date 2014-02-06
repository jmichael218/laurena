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

const class language& iarchive_xml::language() const
{
return XML::language();
}

void iarchive_xml::error_tag_not_expected (const std::string& expected, const std::string& found)
{
std::ostringstream ss;

    this->_tokenizer.prefixErrorMessage(ss);
    ss << "Was expecting </" << expected << "> but found </" << found << ">.";
    throw LAURENA_FAILED_PARSING_EXCEPTION(ss.str().c_str(),this->_tokenizer._ptr);
}

 void iarchive_xml::readAttributes(any& object)
 {

 }

 void iarchive_xml::readEndOfField(const field& f, const std::string& expectedName)
 {
    this->read_token(XML::TOKEN_INFERIOR_SLASH);
    token t = std::move(this->read_token(XML::TOKEN_KEYWORD));
    std::string keyword = anycast<std::string>(t);

    if (keyword != expectedName) // throw exception
        this->error_tag_not_expected(expectedName, keyword);

    this->read_token(XML::TOKEN_SUPERIOR);

 }

 //! Read value of a class field
 void iarchive_xml::readField (const field& f, const std::string& fieldName, any& object)
 {
const descriptor& fd = f.desc();
token t;
any a;

    // READ ATTRIBUTES
    this->readAttributes(object);

    // End of section
    t = std::move(this->read_token(XML::TOKEN_SLASH_SUPERIOR, XML::TOKEN_SUPERIOR));

    if (t._token_id == XML::TOKEN_SLASH_SUPERIOR)
        return;

    // read type format
    if (this->read_custom_field_format(f, object))
    {
        this->readEndOfField(f, fieldName);
        return; 
    }



    if (fd.has(descriptor::Flags::FIELDS))
    {
        assert(false);
    }
    else
    {
        std::string content = this->_tokenizer.readUntil("<", false);
        this->readEndOfField(f, fieldName);
        f.set(object, content);
        return;

    }
    // normal execution
 }

void iarchive_xml::readObject(const std::string& tag, any& object)
{
token t;
std::string keyword;
const descriptor* d = object.desc();

    // READ ATTRIBUTES
    this->readAttributes(object);

    // End of section
    t = std::move(this->read_token(XML::TOKEN_INFERIOR_SLASH, XML::TOKEN_SUPERIOR));


    while(true)
    {
        std::string content = this->_tokenizer.readUntil("<",true);
        if (*this->_tokenizer._ptr == '/')
        {
            // Check that incoming keyword is same than the last one
            this->read_token(XML::TOKEN_SLASH);
            t = std::move(this->read_token( XML::TOKEN_KEYWORD));

            std::string keyword = anycast<std::string>(t);
            if (keyword == tag)
            {
                this->read_token(XML::TOKEN_SUPERIOR);
                //object.desc()->stoa(content, object);
                return;
            }
            else
                this->error_tag_not_expected(tag, keyword);
        }
        else
        {
            // check content is tabs
            if (!const_charsets<>::TABS.validate(content))
            {
                throw LAURENA_FAILED_PARSING_EXCEPTION("Syntax error",this->_tokenizer._ptr);
            }

            // read keyword
            t=std::move(this->read_token(XML::TOKEN_KEYWORD));
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
    this->read_token(XML::TOKEN_INFERIOR);
    t=std::move(this->read_token(XML::TOKEN_KEYWORD));
    _last_keyword = name ;
    keyword = anycast<std::string>(t);
    
    //<! Check than keyword matches
    if (!boost::iequals(name,keyword))      
        this->error_tag_not_expected(name, keyword);

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
