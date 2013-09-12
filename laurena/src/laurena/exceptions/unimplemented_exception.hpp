///
/// \file       unimplemented_exception.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Calling a function unimplemented for this class exception
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Calling a function unimplemented for this class exception
///
#ifndef LAURENA_UNIMPLEMENTED_EXCEPTION_H
#define LAURENA_UNIMPLEMENTED_EXCEPTION_H

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
#include <laurena/exceptions/exception.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*      Definition of the unimplemented Laurena exception                       */ 
/********************************************************************************/ 

class unimplemented_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    unimplemented_exception (const char* message, const char* filename, const char* function, word32 line) ;
    virtual ~unimplemented_exception () {} 

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

};
#define LAURENA_UNIMPLEMENTED_EXCEPTION(msg) laurena::unimplemented_exception(msg,__FILE__,__FUNCTION__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file