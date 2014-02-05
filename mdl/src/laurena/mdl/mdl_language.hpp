///
/// \file     language_mdl.hpp
/// \brief    parsers and tokens for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parsers and tokens for the mdl language
///
#ifndef LAURENA_LANGUAGE_MDL_H
#define LAURENA_LANGUAGE_MDL_H

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
namespace mdl {
/***********************************************************************************/ 
/* Class LexerMDL                                                                  */ 
/***********************************************************************************/ 


class MDL 
{
public:

    enum TOKENS {
        TOKEN_NULLKEYWORD    =0,
        TOKEN_NEW            =1,
        TOKEN_DPOINTS        ,
        TOKEN_EQUAL          ,
        TOKEN_BRACKET_OPEN   ,
        TOKEN_BRACKET_CLOSE  ,

        TOKEN_AT            ,
        TOKEN_SEMICOLON      ,
        TOKEN_PARENTHESIS_OPEN ,
        TOKEN_PARENTHESIS_CLOSE ,
        TOKEN_INJECTION      , // child <- new String : 
        TOKEN_PRIMARY_KEY    ,
        TOKEN_KEYWORD        ,       
        TOKEN_KEYWORD_LIST   , 
        TOKEN_INTEGER        ,
        TOKEN_HEXADECIMAL    ,
        TOKEN_SINGLE_STRING  ,        
        TOKEN_STRING         ,
        TOKEN_MAX           
    };

    enum FLAGS {

        COMPACT = (1<<0),

    };

	static const std::string ANNOTATION_NAME;

    static void init ();
    inline static class language& language() { return MDL::_language; }

    static inline const charset<>&                            charset_keywordlist ()      { return MDL::_charset_keywordList ; }    

    protected:
    static bool                     _init;
    static charset<>                  _charset_keywordList;
    static class language           _language;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
