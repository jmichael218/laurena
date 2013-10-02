///
/// \file     readwhile.hpp
/// \brief    This algorithm read a string as long as a condition is filled
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm read a string as long as a condition is filled
///

#ifndef LAURENA_READWHILE_H
#define LAURENA_READWHILE_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <functional>

#include <laurena/traits/in_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm readwhile                                                  */ 
/*********************************************************************************/ 

template<typename ITERATOR, typename CHARTYPE, typename STRING>
STRING readwhile(ITERATOR first, ITERATOR last, const std::function<bool (const CHARTYPE& )>& condition)
{
	ITERATOR it(first);
	STRING   str;
	while(it != last)
	{
		if (!condition(*it))
			break; 

		str += *it++;
	}
	return str;
}

template<typename T, typename CHARTYPE>
inline
typename in_traits<T>::string readwhile(T& t, const std::function<bool (const CHARTYPE& )>& condition)
{
	return readwhile<typename in_traits<T>::iterator, CHARTYPE, typename in_traits<T>::string>(in_traits<T>::first(t), in_traits<T>::last(t), condition);
}


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif