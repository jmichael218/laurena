///
/// \file     language_mdl.hpp
/// \brief    parsers and tokens for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parsers and tokens for the mdl language
///
#include <laurena/constants/const_charsets.hpp>

#include <laurena/mdl/language_mdl.hpp>

using namespace laurena;
using namespace mdl;

 const std::string		MDL::ANNOTATION_NAME = "mdl" ;

parsers                 MDL::_parsers;
bool                    MDL::_init               = false;
boost::dynamic_bitset<> MDL::_mask_tab_tokens;
charset<>               MDL::_charset_keywordList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t " ;

void MDL::init () 
{
    if ( MDL::_init )
        return;

    MDL::_mask_tab_tokens.resize(MDL::TOKEN_MAX);
    MDL::_mask_tab_tokens.set (MDL::TOKEN_TABS);
    MDL::_mask_tab_tokens.set(MDL::TOKEN_EOL);
    MDL::_mask_tab_tokens.set(MDL::TOKEN_SINGLE_LINE_COMMENT);
    MDL::_mask_tab_tokens.set(MDL::TOKEN_MULTI_LINE_COMMENT_BEGIN);


    parsers& r = MDL::_parsers;
    r.resize(MDL::TOKEN_MAX);

    r [ MDL::TOKEN_NULLKEYWORD ]         = new single_character_parser('_');
    r [ MDL::TOKEN_NEW ]                 = new keyword_parser("new");
    r [ MDL::TOKEN_SINGLE_LINE_COMMENT ] = new keyword_parser("##");
    r [ MDL::TOKEN_MULTI_LINE_COMMENT_BEGIN ] = new keyword_parser("#*");
    r [ MDL::TOKEN_DPOINTS ]             = new single_character_parser(':');
    r [ MDL::TOKEN_EQUAL ]               = new single_character_parser('=');
    r [ MDL::TOKEN_BRACKET_OPEN ]        = new single_character_parser('{');
    r [ MDL::TOKEN_BRACKET_CLOSE ]       = new single_character_parser('}');
    r [ MDL::TOKEN_AT ]                  = new single_character_parser('@');
    r [ MDL::TOKEN_SEMICOLON ]           = new single_character_parser(';');
    r [ MDL::TOKEN_PARENTHESIS_OPEN ]    = new single_character_parser('(');
    r [ MDL::TOKEN_PARENTHESIS_CLOSE ]   = new single_character_parser(')');
    r [ MDL::TOKEN_INJECTION ]           = new keyword_parser("<-");
    r [ MDL::TOKEN_PRIMARY_KEY ]         = new charset_parser(const_charsets<>::IDNAME);
    r [ MDL::TOKEN_KEYWORD  ]            = new charset_parser(const_charsets<>::VARNAME);
    r [ MDL::TOKEN_KEYWORD_LIST ]        = new charset_parser(MDL::_charset_keywordList);
    r [ MDL::TOKEN_INTEGER ]             = new signed_integer_parser();
    r [ MDL::TOKEN_HEXADECIMAL ]         = new hexadecimal_parser();
    r [ MDL::TOKEN_SINGLE_STRING ]       = new string_parser();
    r [ MDL::TOKEN_STRING ]              = new multi_string_parser();
    r [ MDL::TOKEN_EOL ]                 = new eol_parser();
    r [ MDL::TOKEN_TABS ]                = new tabs_parser();

    MDL::_init = true;
}



//End offile
