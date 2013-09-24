///
/// \file     const_chars.hpp
/// \brief    Generation of literal characters based on a chartype
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Generation of literal characters based on a chartype
///

#ifndef LAURENA_CONST_CHARS_H
#define LAURENA_CONST_CHARS_H

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
/*          generation of const chararacters                                     */ 
/*********************************************************************************/ 
template<typename CHARTYPE=char>
class const_chars
{
public:
	static const CHARTYPE MINUS;		// the '-' character
};

template<typename CHARTYPE>
const CHARTYPE const_chars<CHARTYPE>::MINUS ('-');
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
