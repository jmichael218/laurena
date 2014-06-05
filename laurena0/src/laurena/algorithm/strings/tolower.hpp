///
/// \file     tolower.hpp
/// \brief    This algorithm correct a string so it's made of lowercase characters
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm correct a string so it's made of lowercase characters
///

#ifndef LAURENA_TOLOWER_H
#define LAURENA_TOLOWER_H

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
#include <algorithm>
#include <locale>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          algorithm prefix                                                     */ 
/*********************************************************************************/ 

template<typename T>
inline
void tolower(T& str)
{
    typedef typename in_traits<T>::iterator it;
    it start = in_traits<T>::begin(str);
    it end   = in_traits<T>::end(str);
    
    while (start != end)
    {
        *start = std::tolower(*start);
        ++start;
    }
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif