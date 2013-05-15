///
/// \file     iarchive.hpp
/// \brief    Base class for an input archive i.e a class to serialize a class from a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an input archive i.e a class to serialize a class from a file format.
///
#ifndef LAURENA_IARCHIVE_H
#define LAURENA_IARCHIVE_H

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

#include <laurena/descriptors/descriptor.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

class iarchive
{
public:

    /****************************************************************************/ 
    /*          constructors, destructor                                        */ 
    /****************************************************************************/ 

    //! Default constructor
    iarchive ();

    //! destructor
    virtual ~iarchive();
    
    /****************************************************************************/ 
    /*          Virtual functions to redefine for each serializer class         */ 
    /****************************************************************************/ 

    //! parse a content 
    virtual any& parse (const std::string& name, any& destination) = 0 ;
       
    //! clear variables of last parsing
    virtual iarchive& clear () ;

    /****************************************************************************/
    /*      other functions                                                     */ 
    /****************************************************************************/
    inline void logger (std::ostream* logger) { _logger = logger ; }

    /****************************************************************************/
    /*      protected datas                                                  */ 
    /****************************************************************************/ 
    protected:
    std::ostream*           _logger;
    std::string             _source_filename;
    std::istringstream      _data ;

};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
