///
/// \file     serial_manager.hpp
/// \brief    A base manager for a table of serial ID
/// \author   Frederic Manisse
/// \version  1.0
///
/// A base manager for a table of serial ID
///
#ifndef LAURENA_SERIAL_MANAGER_H
#define LAURENA_SERIAL_MANAGER_H

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

#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
#include <laurena/traits/laurena_traits.hpp>

#include <laurena/types/serial_entry.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              forward definition                                              */ 
/********************************************************************************/ 
class persistance;

/********************************************************************************/ 
/*     serial_manager                                                           */ 
/********************************************************************************/ 

class serial_manager
{
    public:

    /****************************************************************************/ 
    /*      constants                                                           */ 
    /****************************************************************************/ 

    static const word64 SERIAL_UNDEFINED = 0xFFFFFFFF;

    /****************************************************************************/ 
    /*      typedefs                                                            */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<serial_manager>         sptr;    

    /****************************************************************************/ 
    /*      constructors, destructor                                            */ 
    /****************************************************************************/     
    serial_manager(const std::string& spipeline);
    serial_manager(const char* spipeline);

    virtual ~serial_manager();

    /****************************************************************************/ 
    /*      virtual functions                                                   */ 
    /****************************************************************************/ 
    virtual void    write(const serial_entry& entry)               = 0;

    virtual void    read  (serial_entry& destination, const std::string& serialKey)      = 0;

    virtual bool    exist (const std::string& serialKey)                    = 0;
    virtual bool    remove(const std::string& serialKey)                    = 0;

    virtual void    load_last_serial()                                      = 0;
    virtual void    save_last_serial()                                      = 0;
    /****************************************************************************/ 
    /*      other functions                                                     */ 
    /****************************************************************************/ 
    bool remove_object(any object);
    word64 new_serial();

    inline const std::string& pipeline() { return this->_pipeline; }
    /****************************************************************************/ 
    /*      protected datas                                                     */ 
    /****************************************************************************/ 
    protected:

    std::string     _pipeline;

    word64          _last_serial;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file