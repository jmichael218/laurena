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

const std::string&  JSON::ANNOTATION_NAME = "format.json" ;

class language          JSON::_language;
bool                    JSON::_init               = false;
charset<>               JSON::_charset_keywordList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t " ;

void JSON::init () 
{
    if ( JSON::_init )
        return;

    JSON::_language.name("json");

    parsers tabs;
    tabs.resize(2);
    tabs[0] = new tabs_parser();
    tabs[1] = new eol_parser();
    JSON::_language.tabs_parsers(std::move(tabs));


    parsers r;
    r.resize(JSON::TOKEN_MAX);

    r [ JSON::TOKEN_DPOINTS ]             = new single_character_parser(':');
    r [ JSON::TOKEN_EQUAL ]               = new single_character_parser('=');
    r [ JSON::TOKEN_BRACKET_OPEN ]        = new single_character_parser('{');
    r [ JSON::TOKEN_BRACKET_CLOSE ]       = new single_character_parser('}');
    r [ JSON::TOKEN_ARRAY_BRACKET_OPEN ]  = new single_character_parser('[');
    r [ JSON::TOKEN_ARRAY_BRACKET_CLOSE ] = new single_character_parser(']');
    r [ JSON::TOKEN_COLON ]               = new single_character_parser(',');
	r [ JSON::TOKEN_DQUOTE ]			  = new single_character_parser('"');
    r [ JSON::TOKEN_INTEGER ]             = new signed_integer_parser();
    r [ JSON::TOKEN_FLOAT ]               = new signed_integer_parser();
    r [ JSON::TOKEN_TRUE ]                = new keyword_parser("true");
    r [ JSON::TOKEN_FALSE ]               = new keyword_parser("false");
	r [ JSON::TOKEN_NULL ]				  = new keyword_parser("null");
    r [ JSON::TOKEN_SINGLE_STRING ]       = new string_parser();

    JSON::_language.tokens_parsers(std::move(r));

    JSON::_init = true;
}
//End of file




//End offile
