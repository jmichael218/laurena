///
/// \file     voidptr.h
/// \brief    cast a pointer to (void*) 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Cast a pointer to (void*) or throw an exception
///

#ifndef LAURENA_VOID_PTR_H
#define LAURENA_VOID_PTR_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              forward declaration                                             */ 
/********************************************************************************/ 

/*********************************************************************************/
/*         voidptr caster                                                        */ 
/*********************************************************************************/ 

template<typename VALUETYPE>
struct voidptr
{
	static void* cast(const VALUETYPE& value) 
    {
        return (void*) &value;
    }
};

template<typename VALUETYPE>
struct voidptr<VALUETYPE*>
{
	static void* cast(const VALUETYPE* value)
    {
        return (void*) value;
    }
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif