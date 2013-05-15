///
/// \file       debug.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      A static class to display messages on the stderr
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This file contains a static global class to send messages on the stderr
///

#ifndef LAURENA_DEBUG_H
#define LAURENA_DEBUG_H

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
/*              debug interface                                                 */ 
/********************************************************************************/ 

///
/// \brief 
///
class debug {

public:   

    /****************************************************************************/ 
    /*          print functions                                                 */ 
    /****************************************************************************/
    static void printStackTrace () ;
    
    static void println (const char* message) ;
    static void println (const std::string& message) ;

    /****************************************************************************/
    /*          protected function                                              */ 
    /****************************************************************************/ 
    protected:

    #if defined(_MSC_VER)
        static void printCrtDbgReport(const char* message);
    #endif

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    public:

    static std::list<std::ostream*>         _outputs;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
