///
/// \file     file_not_found_exception.hpp
/// \brief    A file not found exception
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A file not found exception
///
#ifndef LAURENA_FILE_NOT_FOUND_EXCEPTION_H
#define LAURENA_FILE_NOT_FOUND_EXCEPTION_H

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
/*      Definition of the file not found Laurena exception                      */ 
/********************************************************************************/ 

class file_not_found_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    file_not_found_exception (const char* message, const std::string& fileNotFound, const char* filename, const char* function, word32 line) ;
    virtual ~file_not_found_exception ();

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

    /****************************************************************************/ 
    /*          protected member datas                                          */ 
    /****************************************************************************/ 
    protected:

    std::string _file_not_found;
};
#define LAURENA_FILE_NOT_FOUND_EXCEPTION(msg,fileNotFound) laurena::file_not_found_exception(msg,fileNotFound,__FILE__,__FUNCTION__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file