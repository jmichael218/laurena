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

parsers                 XML::_parsers;
bool                    XML::_init               = false;
boost::dynamic_bitset<> XML::_mask_tab_tokens;

void XML::init () 
{
    if ( XML::_init )
        return;

    XML::_mask_tab_tokens.resize(XML::TOKEN_MAX);
    XML::_mask_tab_tokens.set (XML::TOKEN_TABS);
    XML::_mask_tab_tokens.set(XML::TOKEN_EOL);

    parsers& r = XML::_parsers;
    r.resize(XML::TOKEN_MAX);

    r [ XML::TOKEN_COMMENT_START ]    = new keyword_parser("<!--");
    r [ XML::TOKEN_COMMENT_END ]      = new keyword_parser("-->");
    r [ XML::TOKEN_INFERIOR_SLASH ]   = new keyword_parser("</");
    r [ XML::TOKEN_SLASH_SUPERIOR ]   = new keyword_parser("/>");
    r [ XML::TOKEN_INFERIOR ]         = new single_character_parser('<');
    r [ XML::TOKEN_SUPERIOR ]         = new single_character_parser('>');        
    r [ XML::TOKEN_KEYWORD ]          = new charset_parser(const_charsets<>::VARNAME);
    r [ XML::TOKEN_EQUAL ]            = new single_character_parser('=');
    r [ TOKEN_SLASH ]                 = new single_character_parser('/');
    r [ XML::TOKEN_STRING ]           = new string_parser();
    r [ XML::TOKEN_EOL ]              = new eol_parser();
    r [ XML::TOKEN_TABS ]             = new tabs_parser();

    XML::_init = true;
}



//End offile
