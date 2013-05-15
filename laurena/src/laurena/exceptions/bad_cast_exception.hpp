///
/// \file     bad_cast_exception.hpp
/// \brief    A failed casting exception
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A failed casting exception
///
#ifndef LAURENA_BAD_CAST_EXCEPTION_H
#define LAURENA_BAD_CAST_EXCEPTION_H

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
/*      Definition of the bad cast Laurena exception                            */ 
/********************************************************************************/ 

class bad_cast_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    bad_cast_exception (const char* message, const char* castTypename, const char* valueTypename, const char* filename, word32 line) ;
    virtual ~bad_cast_exception () {} 

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

    /****************************************************************************/ 
    /*          protected member datas                                          */ 
    /****************************************************************************/ 
    protected:

    std::string _cast_typename;
    std::string _value_typename;

};
#define LAURENA_BAD_CAST_EXCEPTION(msg,castTypeName,valueTypeName) laurena::bad_cast_exception(msg,castTypeName,valueTypeName,__FILE__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file