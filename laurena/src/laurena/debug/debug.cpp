///
/// \file     debug.cpp
/// \copyright (C) Copyright 2002-2012 Frederic Manisse
/// \brief    A static class to display messages on the stderr
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This file contains a static global class to send messages on the stderr
///

/********************************************************************************/ 
/*              includes                                                        */ 
/********************************************************************************/ 
#include <laurena/debug/debug.hpp>

#ifndef _WIN32
    #include <execinfo.h>   // For backstrace
#endif

/********************************************************************************/ 
/*              namespaces                                                      */ 
/********************************************************************************/ 
using namespace laurena ;

/********************************************************************************/ 
/*              static field data definitions                                   */ 
/********************************************************************************/ 
std::list<std::ostream*> debug::_outputs;

/********************************************************************************/ 
/*              functions implementation                                        */ 
/********************************************************************************/


/// implementation of debug::printStackTrace
///
/// TODO: implementation for windows visual studio
void debug::printStackTrace ()
{
    #if defined (_MSC_VER)

    #else
        void *stack[40];
        int size;

        // get void*'s for all entries on the stack
        size = backtrace(stack, 40);

        char** strings = backtrace_symbols(stack,size) ;
        if (strings == nullptr) 
        {
            perror("backtrace_symbols");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < size; ++j)
            printf("%s\n", strings[j]);

        free(strings);
        

    #endif
}

#if defined(_MSC_VER) 
/// visual studio only
/// implementation of debug::printCrtDbgReport
void debug::printCrtDbgReport(const char* message)
{
    word32 s = strlen(message);
    if (s < 10000)
        _CrtDbgReport(_CRT_WARN, nullptr , 0 , nullptr , message ) ;
    else
    {
        char buf[1001] ;
        buf[1000]=0;
        word32 len = 0, clen ;
        const char*p = message;
            
        while ( len <= s)
        {
            clen = len + 1000 > s ? s - len : 1000;
            memcpy(buf,p,clen);
            p += clen;
            _CrtDbgReport(_CRT_WARN, nullptr , 0 , nullptr , buf ) ;
        }
    }
}
#endif

/// implementation of debug::println (const char*)
void debug::println(const char* message)
{
    bool is_last_endl = message[strlen(message) -1] == '\n' ;

    // display debug message in the visual studio console
    #if defined(_MSC_VER)        
        debug::printCrtDbgReport(message);

        if (!is_last_endl)
            _CrtDbgReport(_CRT_WARN, nullptr , 0 , nullptr , "\r\n" ) ;
    #endif

    for (std::ostream* i : debug::_outputs)
        (*i) << message << std::endl;
}

/// implementation of debug::println (std::string&)
void debug::println(const std::string& message)
{
    if (!message.length())
        return;

    bool is_last_endl = (message[message.length()-1] == '\n');

    // display debug message in the visual studio console
    #if defined(_MSC_VER)
        if ( message.length () <= 10000 )  
            _CrtDbgReport(_CRT_WARN, nullptr , 0 , nullptr , message.data()) ;
        else
            debug::printCrtDbgReport(message.data());
       
         if (!is_last_endl)
            _CrtDbgReport(_CRT_WARN, nullptr , 0 , nullptr , "\r\n" ) ;
    #endif

    for (std::ostream* i : debug::_outputs)
        (*i) << message << std::endl;
}
//End of file
