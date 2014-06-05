///
/// \file     iequals.hpp
/// \brief    This algorithm is an insensitive char compare, until std::iequals exists
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm is an insensitive char compare, until std::iequals exists
///

#ifndef LAURENA_IEQUALS_H
#define LAURENA_IEQUALS_H

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
#include <locale>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm prefix                                                     */ 
/*********************************************************************************/ 

template<typename ITERATOR_ARG0, typename ITERATOR_ARG1>
bool iequals(ITERATOR_ARG0 arg0, ITERATOR_ARG1 arg1First, ITERATOR_ARG1 arg1Last)
{

	while (arg1First != arg1Last)
		if ( std::tolower(*arg0++) != std::tolower(*arg1First++))
			return false;

	return true;
}

template<typename T0, typename T1>
inline
bool iequals(T0& arg0, T1& arg1)
{
	return 
	(in_traits<T0>::length(arg0) == in_traits<T1>::length(arg1)) ?
	
	    iequals<typename in_traits<T0>::iterator, typename in_traits<T1>::iterator>(in_traits<T0>::begin(arg0), in_traits<T1>::begin(arg1), in_traits<T1>::end(arg1))
	    : false;
	
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif