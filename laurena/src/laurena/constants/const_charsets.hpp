///
/// \file     const_charsets.h
/// \brief    Global character set constants
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Global character set constants
///

#ifndef LAURENA_CHARSET_CONSTANTS_H
#define LAURENA_CHARSET_CONSTANTS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>
#include <laurena/types/charset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              global character sets                                           */ 
/********************************************************************************/ 
extern charset CHARSET_RN ;     // \r\n
extern charset CHARSET_VARNAME ;  // "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
extern charset CHARSET_IDNAME ;    // "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/"
extern charset CHARSET_FULLPATH_FILENAME_SEPARATOR ; // "/\\:" ;
extern charset CHARSET_NUMBER ; // = "0123456789" 
extern charset CHARSET_LOWCASE ; //<! Low case letters
extern charset CHARSET_HEXANUMBER ; // "0123456789abcdefABCDEF";
extern charset CHARSET_TABS ; // \r\n\r and space
extern charset CHARSET_TABS2 ; // \r\t space, no eol
extern charset CHARSET_LETTERS;
extern charset CHARSET_BINARY; // 0 or 1
extern charset CHARSET_ACCENTS; // french accents
extern charset CHARSET_URI; // http uri

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
