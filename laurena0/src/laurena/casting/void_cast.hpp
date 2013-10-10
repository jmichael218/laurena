///
/// \file     voi_cast.h
/// \brief    cast a pointer or a reference to a (void*) ptr
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  cast a pointer or a reference to a (void*) ptr
///

#ifndef LAURENA_VOID_CAST_H
#define LAURENA_VOID_CAST_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/*********************************************************************************/
/*         voidptr caster                                                        */ 
/*********************************************************************************/ 

template<typename VALUETYPE>
struct void_cast
{
	inline
	static void* cast (const VALUETYPE& value) 
	{
		return (void*) &value;
	}
};

template<typename VALUETYPE>
struct void_cast<VALUETYPE*>
{
	inline
	static void* cast (const VALUETYPE* value)
	{
		return (void*) value;
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif