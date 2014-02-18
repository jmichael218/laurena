///
/// \file     oarchive.hpp
/// \brief    Base class for an output archive i.e a class to serialize a class into a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an output archive i.e a class to serialize a class into a file format.
///
#ifndef LAURENA_OARCHIVE_H
#define LAURENA_OARCHIVE_H

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

/*********************************************************************************/
/*          base class for output archives                                       */ 
/*********************************************************************************/ 

class oarchive 
{
public:   

    /****************************************************************************/ 
    /*          typedef                                                         */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<oarchive>       sptr;

    /****************************************************************************/ 
    /*          Constructor, destructor                                         */ 
    /****************************************************************************/ 
    oarchive () ;
    virtual ~oarchive ();

    /****************************************************************************/ 
    /*          Accessing results                                               */ 
    /****************************************************************************/ 

    inline std::ostream&     stream()  { return _data ; }

    /****************************************************************************/ 
    /*          Clearing results                                                */ 
    /****************************************************************************/ 
    virtual oarchive& clear () ;

    /****************************************************************************/ 
    /*          Virtual functions to redefine for each serializer class         */ 
    /****************************************************************************/ 

    virtual oarchive& serialize(const std::string& name, const any& value,bool injection=false)=0;


    /****************************************************************************/
    /*      other functions                                                     */ 
    /****************************************************************************/
    inline void             logger (std::ostream* logger)       { _logger = logger ; }
    inline std::string      str()                               { return _data.str() ; }

    /****************************************************************************/ 
    /*      protected datas                                                     */ 
    /****************************************************************************/ 
    protected:
   
    std::ostringstream  _data ;
    std::ostream*       _logger ;
    
        
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
