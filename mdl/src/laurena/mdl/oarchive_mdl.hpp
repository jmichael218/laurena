///
/// \file     oarchive_mdl.hpp
/// \brief    Class for a mdl output archive i.e a class to serialize a class into the MDL file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a mdl output archive i.e a class to serialize a class into the MDL file format.
///
#ifndef LAURENA_OARCHIVE_MDL_H
#define LAURENA_OARCHIVE_MDL_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace mdl {

/*********************************************************************************/
/*          base class for output archives                                       */ 
/*********************************************************************************/ 

class oarchive_mdl : public oarchive{

    public:   
    oarchive_mdl () ;
    virtual ~oarchive_mdl ();


    /****************************************************************************/ 
    /*          Virtual class to redefine for each serializer class             */ 
    /****************************************************************************/ 

    virtual oarchive& serialize(const std::string& name, const any& value,bool injection=false);
    
    /****************************************************************************/ 
    /*              new functions                                               */ 
    /****************************************************************************/ 
    void serializeFields(const descriptor& cd, const any& value);
    void serializeElements(const descriptor& cd, const any& value);

    static void save(const std::string& filename, const std::string& name, const any& value);
    static std::string& tostring(std::string& destination, const std::string& name, const any& value, word32 flags = 0);

    /****************************************************************************/ 
    /*      protected function                                                  */ 
    /****************************************************************************/ 
    protected:
    std::string     _tab;
    bool            _injection ;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
