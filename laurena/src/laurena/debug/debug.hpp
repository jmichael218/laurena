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
    static void stack_trace () ;
    
    static void println (const char* message) ;
    static void println (const std::string& message) ;

    /****************************************************************************/
    /*          protected function                                              */ 
    /****************************************************************************/ 
    protected:

    #if defined(_MSC_VER)
	    //! \brief For visual studio, display the debug message into visual studio console
	    //! \param message : The message to be displayed
	    //!
	    //! Print a message into visual studio console.
	    //! This function doesn't add a terminal '\n', assuming it's already in the message 
	    //! or that message is multiline
        static void crt_dbg_report(const char* message);
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
