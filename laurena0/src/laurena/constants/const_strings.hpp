///
/// \file     const_strings.hpp
/// \brief    Generation of literal strings based on a chartype
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Generation of literal strings based on a chartype
///

#ifndef LAURENA_CONST_STRINGS_H
#define LAURENA_CONST_STRINGS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/literals/string_literal.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          generation of const charsets                                         */ 
/*********************************************************************************/ 

template<typename CHARTYPE=char>
class const_strings
{
public:

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
