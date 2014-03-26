///
/// \file     failed_parsing_exception.hpp
/// \brief    Describes a failure in a parsing
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describes a failure in a parsing
///
#ifndef LAURENA_FAILED_PARSING_EXCEPTION_H
#define LAURENA_FAILED_PARSING_EXCEPTION_H

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

class failed_parsing_exception : public exception 
{
    public:    
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    failed_parsing_exception (const char* message, const char* source, const char* filename, const char* function, word32 line) ;
    failed_parsing_exception (const char* message, const std::string& source, const char* filename, const char* function, word32 line) ;
    failed_parsing_exception (const char* message, std::istream& source, const char* filename, const char* function, word32 line) ;
    virtual ~failed_parsing_exception () throw () {} 

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     type ()                  const ;
    virtual void            report(std::ostream& destination) const ;


    /****************************************************************************/ 
    /*          protected member datas                                          */ 
    /****************************************************************************/ 
    protected:

    std::string         _source;
};
#define LAURENA_FAILED_PARSING_EXCEPTION(msg,source) laurena::failed_parsing_exception(msg,source,__FILE__,__FUNCTION__,(word32)__LINE__)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file