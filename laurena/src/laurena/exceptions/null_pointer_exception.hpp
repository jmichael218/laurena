///
/// \file       null_pointer_exception.h
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      A null pointer exception
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A null pointer exception
///
#ifndef LAURENA_NULL_POINTER_EXCEPTION_H
#define LAURENA_NULL_POINTER_EXCEPTION_H

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
/*      Definition of the null pointer Laurena exception                        */ 
/********************************************************************************/ 

class null_pointer_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    null_pointer_exception (const char* message, const char* filename, word32 line) ;
    null_pointer_exception (const std::string& message, const char* filename, word32 line) ;
    virtual ~null_pointer_exception () {} 

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

};
#define LAURENA_NULL_POINTER_EXCEPTION(msg) laurena::null_pointer_exception(msg,__FILE__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file