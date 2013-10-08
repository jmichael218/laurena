///
/// \file     is_integer.hpp
/// \brief    This algorithm return true if a string is built as an integer (no size limit)
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm return true if a string is built as an integer (no size limit)
///

#ifndef LAURENA_IS_INTEGER_H
#define LAURENA_IS_INTEGER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/constants/const_charsets.hpp>
#include <laurena/constants/const_chars.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm readinteger                                                */ 
/*********************************************************************************/ 

template<typename CHARTYPE, typename ITERATOR>
bool is_integer(ITERATOR source, ITERATOR last)
{

	if (*source == const_chars<CHARTYPE>::MINUS)	
		source++;

	return const_charsets<CHARTYPE>::NUMBERS.validate(source, last);
}

template<typename T>
inline
bool is_integer(T& t)
{
	return is_integer<typename in_traits<T>::chartype, typename in_traits<T>::iterator>(in_traits<T>::first(t), in_traits<T>::last(t));
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
