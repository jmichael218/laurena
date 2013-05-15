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
        TOKEN_SINGLE_LINE_COMMENT,
        TOKEN_MULTI_LINE_COMMENT_BEGIN,
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
        TOKEN_EOL            ,
        TOKEN_TABS           ,
        TOKEN_MAX           
    };

    enum FLAGS {

        COMPACT = (1<<0),

    };

    static void init ();

    static inline const parsers&                            units ()                    { return MDL::_parsers ; }
    static inline const charset&                            charset_keywordlist ()      { return MDL::_charset_keywordList ; }
    static inline const boost::dynamic_bitset<>             mask_tab_tokens ()          { return MDL::_mask_tab_tokens; }

    

    protected:
    static bool                     _init;
    static charset                  _charset_keywordList;
    static boost::dynamic_bitset<>  _mask_tab_tokens;
    static parsers                  _parsers;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
