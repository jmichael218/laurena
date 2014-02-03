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


any& iarchive_xml::parse   ( const std::string& name, any& object)
{
    /*
const descriptor& descriptor = *object.desc();
token t;
std::string keyword;

    if (_logger) 
        *_logger << "[ArchiveMDL::extract] type='" << name << ", class='" 
              << descriptor.name() << ")." 
                    << std::endl ;

    //<! First keyword found in the file
    this->readExpected(t,MDL::TOKEN_KEYWORD);
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

    // read the ':' after an object Type 
    this->readExpected(t,MDL::TOKEN_DPOINTS);   

    this->readChildObject(descriptor,object , true ) ;
    */
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
