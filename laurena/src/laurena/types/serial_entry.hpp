///
/// \file     serial_entry.hpp
/// \brief    A class describing an entry for serial key managers
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A class describing an entry for serial key managers
///

#ifndef LAURENA_SERIAL_ENTRY_H
#define LAURENA_SERIAL_ENTRY_H

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

/*********************************************************************************/
/*          class serial_entry                                                   */ 
/*********************************************************************************/ 


class serial_entry
{
public:

    /****************************************************************************/ 
    /*      constructors, destructor                                            */ 
    /****************************************************************************/ 
    serial_entry();
    serial_entry(const serial_entry&  s);
    serial_entry(      serial_entry&& s);
    virtual ~serial_entry();

    /****************************************************************************/ 
    /*      operators                                                           */ 
    /****************************************************************************/ 
    serial_entry& operator=(const serial_entry&  s);
    serial_entry& operator=(      serial_entry&& s);
    
    bool operator==(const std::string& s);
    bool operator==(const serial_entry& s);

    /****************************************************************************/ 
    /*          datas                                                           */ 
    /****************************************************************************/ 

    // stringified (if needed) version of the serial value
    std::string         _serial;        

    // persistance pipeline
    std::string         _pipeline;

    // stringified (if nedded) version of the primary key
    std::string         _primary_key;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif