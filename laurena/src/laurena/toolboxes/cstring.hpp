///
/// \file     cstring.hpp
/// \brief    A toolbox of functions for old c string (or char*) , mainly parsing functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for old c string (or char*) , mainly parsing functions
///

#ifndef LAURENA_TOOLBOX_CSTRING_H
#define LAURENA_TOOLBOX_CSTRING_H

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
#include <laurena/types/string_array.hpp>
#include <laurena/types/charset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              interface                                                       */ 
/********************************************************************************/ 
class cstring {
public:
    
    //! return true if str starts with 'expected_prefix' value like Hello starts with 'Hel'  or even 'H'
    static bool startWith(const char* str, const char* expected_prefix, bool caseSensitive=true, word32 size=-1);

    //! read start of a c string as long as characters are elements of a charset
    static std::string  readWhile(const char* source, const charset& characters);
    static word32       readWhile(const char* source, std::string& destination, const charset& characters);

    //! read start of a c string until a character element of a charset is found
    static std::string readUntil(const char* source, const charset& characters);
    static word32      readUntil(const char* source, std::string& destination, const charset& characters);

    //! read start of a c string until a special characters is found
    static std::string readUntil(const char* source, const char character);
    static word32      readUntil(const char* source, std::string& destination, const char character);

    //! advance in source as long as characters are elements of a charset    
    static const char* skipWhile(const char* source, const charset& characters);

    //! read a possibly signed integer of anysize. Return amount of readed characters. Return 0 for a failed parsing
    static word32 readInteger(const char* source, std::string& destination);


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file    