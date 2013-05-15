///
/// \file     language_mdl.hpp
/// \brief    parsers and tokens for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
///
/// parsers and tokens for the mdl language
///
#include <laurena/json/language_json.hpp>

using namespace laurena;
using namespace json;


parsers                 JSON::_parsers;
bool                    JSON::_init               = false;
boost::dynamic_bitset<> JSON::_mask_tab_tokens;
charset                 JSON::_charset_keywordList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t " ;

void JSON::init () 
{
    if ( JSON::_init )
        return;

    JSON::_mask_tab_tokens.resize(JSON::TOKEN_MAX);
    JSON::_mask_tab_tokens.set (JSON::TOKEN_TABS);
    JSON::_mask_tab_tokens.set(JSON::TOKEN_EOL);


    parsers& r = JSON::_parsers;
    r.resize(JSON::TOKEN_MAX);

    r [ JSON::TOKEN_DPOINTS ]             = new single_character_parser(':');
    r [ JSON::TOKEN_EQUAL ]               = new single_character_parser('=');
    r [ JSON::TOKEN_BRACKET_OPEN ]        = new single_character_parser('{');
    r [ JSON::TOKEN_BRACKET_CLOSE ]       = new single_character_parser('}');
    r [ JSON::TOKEN_ARRAY_BRACKET_OPEN ]  = new single_character_parser('[');
    r [ JSON::TOKEN_ARRAY_BRACKET_CLOSE ] = new single_character_parser(']');
    r [ JSON::TOKEN_COLON ]               = new single_character_parser(',');
    r [ JSON::TOKEN_INTEGER ]             = new signed_integer_parser();
    r [ JSON::TOKEN_FLOAT ]               = new signed_integer_parser();
    r [ JSON::TOKEN_TRUE ]                = new keyword_parser("true");
    r [ JSON::TOKEN_FALSE ]               = new keyword_parser("false");
	r [ JSON::TOKEN_NULL ]				  = new keyword_parser("null");
    r [ JSON::TOKEN_SINGLE_STRING ]       = new string_parser();
    r [ JSON::TOKEN_EOL ]                 = new eol_parser();
    r [ JSON::TOKEN_TABS ]                = new tabs_parser();

    JSON::_init = true;
}
//End of file




//End offile
