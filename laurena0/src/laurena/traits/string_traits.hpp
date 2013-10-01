///
/// \file     string_traits.hpp
/// \brief    Deduce subtypes from string classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Deduce from type various subtypes for use in generic parsing functions
///

#ifndef LAURENA_STRING_TRAITS_H
#define LAURENA_STRING_TRAITS_H

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
/*          template of string_traits                                            */ 
/*********************************************************************************/ 

template<typename T>
class string_traits {};

template
<
	typename CHARTYPE
>
class string_traits<std::basic_string<CHARTYPE>>
{
public:

	typedef CHARTYPE			chartype;
	typedef std::true_type      is_string;	
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif