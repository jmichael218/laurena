///
/// \file     language_xml.hpp
/// \brief    parsers and tokens for the xml language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parsers and tokens for the xml language
///
#include <laurena/constants/const_charsets.hpp>

#include <laurena/xml/xml_language.hpp>

using namespace laurena;
using namespace xml;

 const std::string		XML::ANNOTATION_NAME = "format.mdl" ;

class language          XML::_language;
bool                    XML::_init               = false;


void XML::init () 
{
    if ( XML::_init )
        return;

    XML::_language.name("xml");

    parsers tabs;
    tabs.resize(3);
    tabs[0] = new tabs_parser();
    tabs[1] = new eol_parser();
    tabs[2] = new keyword_to_keyword_parser("<!--", "-->"); 
    XML::_language.tabs_parsers(std::move(tabs));

    parsers r;
    r.resize(XML::TOKEN_MAX);

    r [ XML::TOKEN_INFERIOR_SLASH ]   = new keyword_parser("</");
    r [ XML::TOKEN_SLASH_SUPERIOR ]   = new keyword_parser("/>");
    r [ XML::TOKEN_INFERIOR ]         = new single_character_parser('<');
    r [ XML::TOKEN_SUPERIOR ]         = new single_character_parser('>');        
    r [ XML::TOKEN_KEYWORD ]          = new charset_parser(const_charsets<>::VARNAME);
    r [ XML::TOKEN_EQUAL ]            = new single_character_parser('=');
    r [ TOKEN_SLASH ]                 = new single_character_parser('/');
    r [ XML::TOKEN_STRING ]           = new string_parser();

    XML::_language.tokens_parsers(std::move(r));

    XML::_init = true;
}



//End offile
