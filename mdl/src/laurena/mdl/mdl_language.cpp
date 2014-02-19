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

#include <laurena/mdl/mdl_language.hpp>
#include <laurena/mdl/iarchive_mdl.hpp>
#include <laurena/mdl/oarchive_mdl.hpp>

using namespace laurena;
using namespace mdl;

const std::string		MDL::ANNOTATION_NAME = "format.mdl" ;

bool                    MDL::_init               = false;
charset<>               MDL::_charset_keywordList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t " ;
language                MDL::_language;

iarchive::sptr mdl_iarchive_constructor()
{
    return std::make_shared<iarchive_mdl>();
}

oarchive::sptr mdl_oarchive_constructor()
{
    return std::make_shared<oarchive_mdl>();


}
void MDL::init () 
{
    if ( MDL::_init )
        return;

    MDL::_language.name ("mdl");

    parsers tabs;
    tabs.resize(4);
    tabs[0] = new tabs_parser();
    tabs[1] = new eol_parser();
    tabs[2] = new keyword_to_charset_parser("##", const_charsets<>::RN);
    tabs[3] = new keyword_to_keyword_parser("#*", "*#"); 
    MDL::_language.tabs_parsers(std::move(tabs));

    parsers r;
    r.resize(MDL::TOKEN_MAX);

    r [ MDL::TOKEN_NULLKEYWORD ]         = new single_character_parser('_');
    r [ MDL::TOKEN_NEW ]                 = new keyword_parser("new");
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

    MDL::_language.tokens_parsers(std::move(r));
    MDL::_language.writer_constructor(mdl_oarchive_constructor);
    MDL::_language.reader_constructor(mdl_iarchive_constructor);

    MDL::_init = true;
}



//End offile
