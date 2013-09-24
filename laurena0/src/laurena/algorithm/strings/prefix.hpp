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

template<typename STRING>
inline
bool prefix(const STRING& str, const STRING& expected_prefix, size_t size_prefix=-1)
{
	return prefix(str.data(), expected_prefix.data(), expected_prefix.data() + (size_prefix==-1 ? expected_prefix.length() : size_prefix));
}

template<typename CHARTYPE>
inline
bool prefix(const CHARTYPE* str, const CHARTYPE* expected_prefix, size_t size_prefix=-1)
{
	return prefix(str, expected_prefix, expected_prefix + (size_prefix==-1 ? std::char_traits<CHARTYPE>::length(expected_prefix) : size_prefix));
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif