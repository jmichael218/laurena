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
/*          algorithm prefix                                                     */ 
/*********************************************************************************/ 

template<typename CHARTYPE>
std::basic_string<CHARTYPE> readwhile(const CHARTYPE* source, const charset<CHARTYPE>& characters)
{
	const CHARTYPE* p (source);
	while(true)
	{
		if (characters.test(*p) == false)
			break; 

		++p;
	}
	return std::basic_string<CHARTYPE>(source,p);
}

template<typename CHARTYPE>
inline
std::basic_string<CHARTYPE> readwhile(const std::basic_string<CHARTYPE>& source, const charset<CHARTYPE>& characters)
{
	return readwhile(source.data(),characters);
}

template<typename CHARTYPE>
std::basic_string<CHARTYPE> readwhile(std::basic_istream<CHARTYPE>& source, const charset<CHARTYPE>& characters)
{
	std::basic_stringbuf<CHARTYPE> buf;
	CHARTYPE c;

	while (!source.eof())
	{
		c = source.peek();

		if (characters.test(c) == false)
			break;

		buf.sputc(c);
		source.ignore(1);
	}

	return buf.str();
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif