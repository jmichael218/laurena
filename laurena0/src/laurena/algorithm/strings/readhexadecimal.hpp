///
/// \file     readhexadecimal.hpp
/// \brief    This algorithm read a string as long as it looks like an hexadecimal integer 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm read a string as long as it looks like an hexadecimal integer 
///

#ifndef LAURENA_READ_HEXADECIMAL_H
#define LAURENA_READ_HEXADECIMAL_H

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
STRING readhexadecimal(ITERATOR source, ITERATOR last)
{
	return readwhile<ITERATOR,CHARTYPE,STRING>(source, last, const_charsets<CHARTYPE>::HEXADECIMAL.condition());
}

template<typename T>
inline
typename in_traits<T>::string readhexadecimal(T& t)
{
	return readhexadecimal<typename in_traits<T>::chartype, typename in_traits<T>::iterator, typename in_traits<T>::string>(in_traits<T>::begin(t), in_traits<T>::end(t));
}
 
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
