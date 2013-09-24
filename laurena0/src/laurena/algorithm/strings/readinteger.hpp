///
/// \file     readinteger.hpp
/// \brief    This algorithm read a string as long as it looks like an integer : -32fdsksdkf => -32
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm read a string as long as it looks like an integer : -32fdsksdkf => -32
///

#ifndef LAURENA_READINTEGER_H
#define LAURENA_READINTEGER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/constants/const_charsets.hpp>
#include <laurena/constants/const_chars.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm readinteger                                                */ 
/*********************************************************************************/ 

template<typename CHARTYPE, typename ITERATOR, typename STRING>
STRING readinteger(ITERATOR source)
{
ITERATOR it (source);
STRING   destination;

	if (*source == const_chars<CHARTYPE>::MINUS)	
		destination += *source++;

	return destination += readwhile<ITERATOR,const charset<CHARTYPE>&,STRING>(source,const_charsets<CHARTYPE>::NUMBERS);
}

template<typename CHARTYPE>
inline
std::basic_string<CHARTYPE> readinteger(const std::basic_string<CHARTYPE>& source)
{
	return readinteger<CHARTYPE, const CHARTYPE*, std::basic_string<CHARTYPE>>(source.data());
}

template<typename CHARTYPE, typename ISTREAM, typename ISTREAM_ITERATOR, typename STRING>
STRING readinteger(ISTREAM& source)
{
	return readinteger<CHARTYPE, ISTREAM_ITERATOR, STRING>((ISTREAM_ITERATOR(source)));
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
