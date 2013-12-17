///
/// \file     prefix.hpp
/// \brief    This algorithm checks if a string start with an expected value
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm checks if a string start with an expected value
///

#ifndef LAURENA_PREFIX_H
#define LAURENA_PREFIX_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/traits/in_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm prefix                                                     */ 
/*********************************************************************************/ 

template<typename ITERATOR_SOURCE, typename ITERATOR_PREFIX>
bool prefix(ITERATOR_SOURCE source, ITERATOR_PREFIX prefixFirst, ITERATOR_PREFIX prefixLast)
{

	while (prefixFirst != prefixLast)
		if (*source++ != *prefixFirst++)
			return false;

	return true;
}

template<typename T0, typename T1>
inline
bool prefix(T0& source, const T1& tprefix)
{
	return prefix<typename in_traits<T0>::iterator, typename in_traits<T1>::iterator>(in_traits<T0>::begin(source), in_traits<T1>::begin(tprefix), in_traits<T1>::end(tprefix));
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif