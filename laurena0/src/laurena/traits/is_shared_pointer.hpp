///
/// \file     is_shared_pointer.hpp
/// \brief    Deduce if a type is a shared pointer
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Deduce if a type is a shared pointer
///

#ifndef LAURENA_IS_SHARED_POINTER_H
#define LAURENA_IS_SHARED_POINTER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <memory>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          trait is shared pointer                                              */ 
/*********************************************************************************/ 
template<typename T> 
struct is_shared_pointer : std::false_type {};

template<typename T > 
struct is_shared_pointer<std::shared_ptr<T>> : std::true_type {};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif