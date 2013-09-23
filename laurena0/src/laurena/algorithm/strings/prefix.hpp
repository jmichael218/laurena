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

#include <string>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm prefix                                                     */ 
/*********************************************************************************/ 

template<typename CHARTYPE>
bool prefix(const CHARTYPE* str, const CHARTYPE* expected_prefix, size_t size=-1)
{
	if (size == -1)
		size = std::char_traits<CHARTYPE>::length(expected_prefix);

	while (*str && size--)
		if (*str++ != *expected_prefix++)
			return false;

	return true;
}

template<typename STRING>
inline
bool prefix(const STRING& str, const STRING& expected_prefix, size_t size=-1)
{
	return prefix(str.data(), expected_prefix.data(), size==-1 ? expected_prefix.length() : size);
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif