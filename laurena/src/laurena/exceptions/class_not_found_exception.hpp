///
/// \file       class_not_found_exception.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      An exception occuring when a class descriptor is null
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An exception occuring when a class descriptor is null
///
#ifndef LAURENA_CLASS_NOT_FOUND_EXCEPTION_H
#define LAURENA_CLASS_NOT_FOUND_EXCEPTION_H

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

class class_not_found_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    class_not_found_exception (const type_info& type, const char* message, const char* filename, const char* function, word32 line) ;
    class_not_found_exception (const type_info& type, const std::string& message, const char* filename, const char* function, word32 line) ;
    virtual ~class_not_found_exception () throw () {} 

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

    /****************************************************************************/ 
    /*          protected member datas                                          */ 
    /****************************************************************************/ 
    protected:

    const type_info&        _type;

};
#define LAURENA_CLASS_NOT_FOUND_EXCEPTION(type, msg) laurena::class_not_found_exception(type, msg,__FILE__,__FUNCTION__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file