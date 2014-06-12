///
/// \file       includes.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Include header files used everywhere.
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This file include the C / C++ / boost headers for each supported plateform. 
/// There should not be another place with headers included in the code.
///

#ifndef LAURENA_INCLUDES_H
#define LAURENA_INCLUDES_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*                                                                              */ 
/*          various define you can set on or off                                */ 
/*                                                                              */ 
/********************************************************************************/ 

#define LAURENA_DEBUG_CLASSES

/********************************************************************************/ 
/*																				*/ 
/*			definitions for win 32 compilations				    				*/ 
/*																				*/ 
/********************************************************************************/ 
#if defined(_WIN32)

    // These extra redefine are to avoid tons of warnings with .NET 2005 
    // which deprecates classics libc functions.
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
    #endif

    #ifndef _CRT_SECURE_NO_DEPRECATE 
        #define _CRT_SECURE_NO_DEPRECATE
    #endif

    #ifndef _SCL_SECURE_NO_WARNINGS
        #define _SCL_SECURE_NO_WARNINGS
    #endif

    #pragma warning( disable : 4820 4710 4514 4668 4626 4512 4100)

    #pragma warning( push, 1 )
#endif

/********************************************************************************/ 
/*  classic C includes                                                          */ 
/********************************************************************************/ 

    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    #include <time.h>
    #include <malloc.h>
    #include <assert.h>
    #include <stdlib.h>


#if defined(_WIN32)

    // Windows Only
    #include <crtdbg.h>
    //#include <windows.h>

#else

// supposed linux
    #include <limits.h>
    #include <unistd.h>
#endif

/********************************************************************************/ 
/*      STL includes                                                            */ 
/********************************************************************************/ 
#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream> 
#include <list>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <typeindex>			// used in classes.hpp
#include <memory>
		
/********************************************************************************/ 
/* boost includes                                                               */ 
/********************************************************************************/ 

#include <boost/dynamic_bitset.hpp>
#include <boost/iostreams/stream.hpp>
//#include <boost/lexical_cast.hpp>


/********************************************************************************/ 
/*              macros                                                          */ 
/********************************************************************************/ 

#ifndef LOWER
    #define LOWER(c) (((c)>='A' && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))
#endif

#ifndef UPPER
    #define UPPER(c) (((c)>='a' && (c) <= 'z') ? ((c)+('A'-'a')) : (c))
#endif

#if defined (_WIN32)
    #pragma warning( pop )

    #define do_sleep(ms) Sleep(ms)
    #define LAURENA_STRDUP(s) _strdup(s)

#else
    //supposed linux
    #define do_sleep(ms) usleep((ms)*1000)
    #define LAURENA_STRDUP(s) strdup(s)
    typedef std::type_info type_info;
#endif

#endif
// end of file
