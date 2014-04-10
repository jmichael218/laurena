///
/// \file     dao.hpp
/// \brief    DAO base class and templated class
/// \author   Frederic Manisse
/// \version  1.0
///
/// DAO base class and templated class
///
#ifndef LAURENA_DAO_H
#define LAURENA_DAO_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*     dao                                                                      */ 
/********************************************************************************/ 

class dao
{
public:

    /****************************************************************************/ 
    /*          typedef                                                         */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<dao>       sptr;

    /****************************************************************************/ 
    /*          destructor, constructors                                        */ 
    /****************************************************************************/ 
    dao (const descriptor& desc);
    virtual ~dao();

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual any&    read    (const any& primaryKey, any& destination)=0;
    virtual any     read    (const any& primaryKey);

    virtual any&    create  (any& object)               =0;
    virtual any&    update  (any& object)               =0;
    virtual void    erase   (any& object)               =0;
    virtual void    erase   (const any& primaryKey)     =0;

    virtual bool    exist   (const any& primaryKey)     =0;

    /****************************************************************************/ 
    /*          accessors                                                       */ 
    /****************************************************************************/ 

    inline
    const std::string& serial_manager() const { return this->_serial_manager; }

    inline
    void serial_manager(const std::string& s) { this->_serial_manager = s; }

    inline
    void serial_manager(const char* s) { this->_serial_manager = s; }

    inline
    const descriptor& desc() const { return this->_descriptor; }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    const descriptor&       _descriptor;
    std::string             _serial_manager;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file