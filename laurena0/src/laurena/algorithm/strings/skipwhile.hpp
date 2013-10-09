///
/// \file     skipwhile.hpp
/// \brief    This algorithm skip string characters as long as a condition is filled
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm skip string characters as long as a condition is filled
///

#ifndef LAURENA_SKIPWHILE_H
#define LAURENA_SKIPWHILE_H

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

template<typename ITERATOR, typename CHARTYPE>
ITERATOR skipwhile(ITERATOR first, ITERATOR last, const std::function<bool (const CHARTYPE& )>& condition)
{
	ITERATOR it(first);
	while(it != last)
	{
		if (!condition(*it))
			return it;

		it++;
	}
	return it;
}

template<typename T, typename CHARTYPE>
inline
typename in_traits<T>::iterator skipwhile(T& t, const std::function<bool (const CHARTYPE& )>& condition)
{
	return skipwhile<typename in_traits<T>::iterator, CHARTYPE>(in_traits<T>::first(t), in_traits<T>::last(t), condition);
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif