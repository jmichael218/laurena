///
/// \file     string_literal.hpp
/// \brief    Generation of string literals depending of char types
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Generation of string literals depending of char types
///

#ifndef LAURENA_STRING_LITERAL_H
#define LAURENA_STRING_LITERAL_H

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
/*          generation of string literals                                        */ 
/*********************************************************************************/ 

template<typename CHARTYPE>
std::basic_string<CHARTYPE> sliteral(const char* value)
{	

	std::basic_string<CHARTYPE> s;

	if (value)
		s.assign(value, value+strlen(value));

	return s;
}


template<typename CHARTYPE>
inline
CHARTYPE cliteral(char value)
{
	return (CHARTYPE) value;
}
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif