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

template<typename ITERATOR>
bool prefix(ITERATOR source, ITERATOR prefixFirst, ITERATOR prefixLast)
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
	return prefix<in_traits<T0>::iterator>(in_traits<T0>::first(source), in_traits<T1>::first(tprefix), in_traits<T1>::last(tprefix));
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif