///
/// \file     language_xml.hpp
/// \brief    parsers and tokens for the xml language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parsers and tokens for the xml language
///
#ifndef LAURENA_LANGUAGE_XML_H
#define LAURENA_LANGUAGE_XML_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace xml {
/***********************************************************************************/ 
/* Class LexerMDL                                                                  */ 
/***********************************************************************************/ 


class XML 
{
public:

    enum TOKENS {
        TOKEN_INFERIOR_SLASH =0,
        TOKEN_INFERIOR       ,
        TOKEN_SLASH_SUPERIOR ,
        TOKEN_SLASH          ,
        TOKEN_SUPERIOR       ,
        TOKEN_KEYWORD        ,
        TOKEN_EQUAL          ,
        TOKEN_STRING         ,
        TOKEN_MAX           
    };

    enum FLAGS {

        COMPACT = (1<<0),

    };

	static const std::string ANNOTATION_NAME;

    static void init (); 

    inline static class language& language() { return XML::_language; }

    protected:
    static bool                     _init;
    static class language           _language;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
