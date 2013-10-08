///
/// \file     language_json.hpp
/// \brief    parsers and tokens for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
///
/// parsers and tokens for the json language
///
#ifndef LAURENA_LANGUAGE_JSON_H
#define LAURENA_LANGUAGE_JSON_H

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
namespace json {

/***********************************************************************************/ 
/* Class JSON                                                                      */ 
/***********************************************************************************/ 

class JSON
{
public:

    enum TOKENS {
        TOKEN_DPOINTS        =0,
        TOKEN_EQUAL          ,
        TOKEN_BRACKET_OPEN   ,
        TOKEN_BRACKET_CLOSE  ,
        TOKEN_ARRAY_BRACKET_OPEN,
        TOKEN_ARRAY_BRACKET_CLOSE,

        TOKEN_COLON          ,
        TOKEN_INTEGER        ,
        TOKEN_FLOAT          ,
        TOKEN_TRUE           ,
        TOKEN_FALSE          , 
		TOKEN_NULL			 ,
        TOKEN_SINGLE_STRING  ,        
        TOKEN_EOL            ,
        TOKEN_TABS           ,
		TOKEN_DQUOTE		 ,
        TOKEN_MAX           
    };

	static const std::string& ANNOTATION_NAME ;

    static void init ();

    static inline const parsers&                            units ()                    { return JSON::_parsers ; }
    static inline const charset<>&                            charset_keywordlist ()      { return JSON::_charset_keywordList ; }
    static inline const boost::dynamic_bitset<>             mask_tab_tokens ()          { return JSON::_mask_tab_tokens; }

    

    protected:
    static bool                     _init;
    static charset<>                  _charset_keywordList;
    static boost::dynamic_bitset<>  _mask_tab_tokens;
    static parsers                  _parsers;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
