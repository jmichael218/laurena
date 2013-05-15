///
/// \file     stdstring.hpp
/// \brief    A toolbox of functions for std::string, mainly parsing functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for std::string, mainly parsing functions
///

#ifndef LAURENA_TOOLBOX_STDSTRING_H
#define LAURENA_TOOLBOX_STDSTRING_H

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
class stdstring {
public:

    //! Return true if parameter matche the integer regex, without size limitation
    static bool isInteger(const std::string& value);

    static bool startWith(const std::string& str, const std::string& expected_prefix, bool caseSensitive=false);


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file    