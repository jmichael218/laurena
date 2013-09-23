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

#include <string>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm alphabet                                                   */ 
/*********************************************************************************/ 

template<typename CHARTYPE>
std::basic_string<CHARTYPE>  alphabet (const CHARTYPE* first, const CHARTYPE* end)
{
	std::basic_string<CHARTYPE> a;
	while (first != end)
	{
		if (a.find_first_of(*first) == std::basic_string<CHARTYPE>::npos)
			a += *first;
		++first;
	}

	return a;
}


template<typename CHARTYPE>
inline 
std::basic_string<CHARTYPE> alphabet (const CHARTYPE* first)
{
	return alphabet<CHARTYPE>(first, first + std::char_traits<CHARTYPE>::length(first));
}

template<typename CHARTYPE> 
inline
std::basic_string<CHARTYPE> alphabet(const std::basic_string<CHARTYPE>& str)
{
	return alphabet<CHARTYPE>(str.data(), str.data()+str.length());
}


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif