///
/// \file       types.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      integer types redefinitions per bit sizes
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This file redefine (un)signed ints types per bits size. 
/// int are signed types while word are unsigned types.
///

#ifndef LAURENA_TYPES_H
#define LAURENA_TYPES_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/ 
/*                  basic typedefs                                               */ 
/*********************************************************************************/ 

/// intXX is for signed values
/// wordXX is for unsigned values

/// \brief typedef for unsigned 8 bits integers
///
/// word8 is the typedef for unsigned 8 bits integers
typedef unsigned char       word8 ;     //<! unsigned 8 bits integer

/// \brief typedef for signed 8 bits integers
///
/// int8 is the typedef for signed 8 bits integers
typedef signed char         int8 ;      //<! signed 8 bits integer

typedef unsigned short int  word16 ;    //<! unsigned 16 bits integer
typedef signed short int    int16 ;     //<! signed 16 bits integer

typedef unsigned int        word32 ;    //<! unsigned 32 bits integer
typedef signed int          int32 ;     //<! signed 32 bits integer

/// 64 bits types
#ifdef WIN32
  typedef unsigned __int64 word64 ;   //<! unsigned 64 bits integer
#else
  typedef unsigned long long int word64 ; //<! unsigned 64 bits integer
#endif  

#ifdef WIN32
  typedef signed __int64 int64 ;      //<! signed 64 bits integer
#else
  typedef signed long long int int64 ;    //<! unsigned 64 bits integer
#endif  

#ifndef LLONG_MIN
  #define LLONG_MIN    LONG_LONG_MIN
#endif

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//end of file    

