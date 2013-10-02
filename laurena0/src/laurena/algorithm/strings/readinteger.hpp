///
/// \file     readinteger.hpp
/// \brief    This algorithm read a string as long as it looks like an integer : -32fdsksdkf => -32
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm read a string as long as it looks like an integer : -32fdsksdkf => -32
///

#ifndef LAURENA_READINTEGER_H
#define LAURENA_READINTEGER_H

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

template<typename CHARTYPE, typename ITERATOR, typename STRING>
STRING readinteger(ITERATOR source, ITERATOR last)
{
STRING   destination;

	if (*source == const_chars<CHARTYPE>::MINUS)	
		destination += *source++;

	return destination += readwhile<ITERATOR,CHARTYPE,STRING>(source, last, const_charsets<CHARTYPE>::NUMBERS.condition());
}

template<typename T>
inline
typename in_traits<T>::string readinteger(T& t)
{
	return readinteger<typename in_traits<T>::chartype, typename in_traits<T>::iterator, typename in_traits<T>::string>(in_traits<T>::first(t), in_traits<T>::last(t));
}
 
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
