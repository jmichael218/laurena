///
/// \file       memory_functions.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Functions to manipulate offsets and pointers
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Functions to manipulate offsets and pointers
///

#ifndef LAURENA_MEMORY_FUNCTIONS_H
#define LAURENA_MEMORY_FUNCTIONS_H

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
namespace memory {

/*********************************************************************************/ 
/*      other functions                                                          */ 
/*********************************************************************************/ 

/// return difference in bytes between 2 pointers
/// used by the script langage classes and the memory pool class
int32 offset (const void * pBase ,const void * pDest );


inline word8** ptr(const void* pBase, word32 offset)
#ifdef _WIN32
    { return reinterpret_cast<word8**>( ((word64) pBase) + offset ) ; }
#else
    { return reinterpret_cast<word8**>( ((word32) pBase) + offset) ; }
#endif

/// macro to compute offset of a field in a class
#define field_offset(CLASSNAME,FIELD) [] () -> word32 { CLASSNAME ST_OFFSET; return laurena::memory::offset(&ST_OFFSET,&ST_OFFSET.FIELD); } ()

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
