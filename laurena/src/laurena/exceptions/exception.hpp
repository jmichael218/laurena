///
/// \file       exception.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      The base exception for all exception of the library
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// The base exception for all exception of the library
///

#ifndef LAURENA_EXCEPTION_H
#define LAURENA_EXCEPTION_H

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
/*      Definition of the standard Laurena exception                            */ 
/********************************************************************************/ 

class exception : public std::exception
{
    /****************************************************************************/ 
    /*          constructor, destructors                                        */ 
    /****************************************************************************/ 
    public:
    exception (const char* message, const char* filename , word32 line) ;
    exception (const std::string& message, const char* filename, word32 line);
    exception (const std::ostringstream& message, const char* filename, word32 line);

    virtual ~exception ();

    /****************************************************************************/
    /*          virtual functions from std::exception                           */ 
    /****************************************************************************/
    virtual const char* what() const throw();

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual const char*     exceptionType ()                  const ;
    virtual void            report(std::ostream& destination) const ;

    /****************************************************************************/ 
    /*          reporting                                                       */ 
    /****************************************************************************/ 
    void print () const ;
    

    /****************************************************************************/ 
    /*          getters                                                         */ 
    /****************************************************************************/

    inline const std::string& message () const { return this->_message ; }
    inline word32             line()     const { return this->_line; }
    inline const std::string& filename() const { return this->_filename;}
    
    /****************************************************************************/
    /*          protected functions                                             */ 
    /****************************************************************************/
    protected:

    void ready();

    /****************************************************************************/ 
    /*          protected member datas                                          */ 
    /****************************************************************************/ 
    protected:
    word32           _line ;
    std::string      _filename ;
    std::string      _message ;
    std::string      _what;
};
#define LAURENA_EXCEPTION(msg) laurena::exception(msg,__FILE__,(word32)__LINE__)



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//end of file
