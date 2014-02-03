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
        TOKEN_COMMENT_START  = 0,
        TOKEN_COMMENT_END    ,
        TOKEN_INFERIOR_SLASH ,
        TOKEN_INFERIOR       ,
        TOKEN_SLASH_SUPERIOR ,
        TOKEN_SLASH          ,
        TOKEN_SUPERIOR       ,
        TOKEN_KEYWORD        ,
        TOKEN_EQUAL          ,

        TOKEN_STRING         ,
        TOKEN_EOL            ,
        TOKEN_TABS           ,
        TOKEN_MAX           
    };

    enum FLAGS {

        COMPACT = (1<<0),

    };

	static const std::string ANNOTATION_NAME;

    static void init ();

    static inline const parsers&                            units ()                    { return XML::_parsers ; }
    static inline const boost::dynamic_bitset<>             mask_tab_tokens ()          { return XML::_mask_tab_tokens; }

    

    protected:
    static bool                     _init;
    static boost::dynamic_bitset<>  _mask_tab_tokens;
    static parsers                  _parsers;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
