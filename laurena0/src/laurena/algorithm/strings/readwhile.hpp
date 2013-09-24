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

#include <laurena/types/charset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm readwhile                                                  */ 
/*********************************************************************************/ 

template<typename ITERATOR, typename CHARSET, typename STRING>
STRING readwhile(ITERATOR source, CHARSET characters)
{
	ITERATOR it (source);
	while(true)
	{
		if (characters.test(*it) == false)
			break; 

		++it;
	}
	return STRING(source,it);
}

template<typename CHARTYPE>
inline
std::basic_string<CHARTYPE> readwhile(const std::basic_string<CHARTYPE>& source, const charset<CHARTYPE>& characters)
{
	return readwhile<const CHARTYPE*, const charset<CHARTYPE>&, std::basic_string<CHARTYPE>>(source.data(),characters);
}

template<typename ISTREAM, typename ISTREAM_ITERATOR, typename CHARSET, typename STRING>
STRING readwhile(ISTREAM& source, CHARSET characters)
{
	return readwhile<ISTREAM_ITERATOR, CHARSET, STRING>((ISTREAM_ITERATOR(source)), characters);
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif