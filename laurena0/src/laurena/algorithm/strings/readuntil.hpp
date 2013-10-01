///
/// \file     readuntil.hpp
/// \brief    This algorithm read a string until a condition is filled
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This algorithm read a string until a condition is filled
///

#ifndef LAURENA_READUNTIL_H
#define LAURENA_READUNTIL_H

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
/*          algorithm readuntil                                                  */ 
/*********************************************************************************/ 

template<typename ITERATOR, typename CHARSET, typename STRING>
STRING readuntil(ITERATOR first, ITERATOR last, const CHARSET& characters)
{
	ITERATOR it(first);
	STRING   str;
	while(it != last)
	{
		if (characters.test(*it) == true)
			break; 

		str += *it++;
	}
	return str;
}

template<typename T, typename CHARSET>
inline
typename in_traits<T>::string readuntil(T& t, const CHARSET& cset)
{
	return readuntil<typename in_traits<T>::iterator, CHARSET, typename in_traits<T>::string>(in_traits<T>::first(t), in_traits<T>::last(t), cset);
}


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
