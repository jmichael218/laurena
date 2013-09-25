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
STRING readwhile(ITERATOR first, ITERATOR last, const CHARSET& characters)
{
	ITERATOR it(first);
	STRING   str;
	while(it != last)
	{
		if (characters.test(*it) == false)
			break; 

		str += *it++;
	}
	return str;
}

template<typename T, typename CHARSET>
inline
typename in_traits<T>::string readwhile(T& t, const CHARSET& cset)
{
	return readwhile<typename in_traits<T>::iterator, CHARSET, typename in_traits<T>::string>(in_traits<T>::first(t), in_traits<T>::last(t), cset);
}


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif