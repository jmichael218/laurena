///
/// \file     memory_functions.cpp
/// \copyright (C) Copyright 2002-2012 Frederic Manisse
/// \brief    Functions to manipulate offsets and pointers
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Functions to manipulate offsets and pointers
///

#include <laurena/memory/memory_functions.hpp>

using namespace laurena;
using namespace memory;

/********************************************************************************/ 
/*                                                                              */ 
/*  usefull & various others functions                                          */ 
/*                                                                              */ 
/********************************************************************************/ 

int32 laurena::memory::offset (const void * pBase ,const void * pDest )
{
    #ifdef _WIN32
        __int64 basei = reinterpret_cast<__int64>(pBase);
        __int64 offseti = reinterpret_cast<__int64>(pDest);
        return (int32) (offseti - basei);
    #else /// suposed linux
        long long int basei = (( long long int ) pBase ) ;
        long long int offseti = ( long long int ) pDest ;
        return (int32) (offseti - basei)  ;
    #endif
}
//End of file
