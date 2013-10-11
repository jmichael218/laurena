///
/// \file     type_traits.hpp
/// \brief    Deduce subtypes from a type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Deduce subtypes from a type

#ifndef LAURENA_TYPE_TRAITS_H
#define LAURENA_TYPE_TRAITS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include  <type_traits>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          template of string_traits                                            */ 
/*********************************************************************************/ 

template<typename T>
struct traits 
{
public:

	typedef typename std::remove_pointer< typename std::remove_reference<typename std::remove_const<T>::type>::type>::type basetype;

};

template<>
struct traits<void*>
{
	typedef void basetype;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif