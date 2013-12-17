///
/// \file     alphabet.hpp
/// \brief    This algorithm computes the minimal set of characters needed to write a string parameter
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm computes the minimal set of characters needed to write a string parameter
///

#ifndef LAURENA_ALPHABET_H
#define LAURENA_ALPHABET_H

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
/*          algorithm alphabet                                                   */ 
/*********************************************************************************/ 

template<typename ITERATOR, typename STRING>
STRING  alphabet (ITERATOR first, ITERATOR end)
{
	STRING a;
	while (first != end)
	{
		if (a.find_first_of(*first) == STRING::npos)
			a += *first;
		++first;
	}

	return a;
}

template<typename T>
inline
typename in_traits<T>::string alphabet(T& t)
{
	return alphabet<typename in_traits<T>::iterator, in_traits<T>::string>(in_traits<T>::begin(t), in_traits<T>::end(t));
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif