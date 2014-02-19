///
/// \file     persistance.hpp
/// \brief    Generic persistance engine
/// \author   Frederic Manisse
/// \version  1.0
///
/// Generic persistance engine
///
#ifndef LAURENA_PERSISTANCE_H
#define LAURENA_PERSISTANCE_H

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
#include <laurena/persistance/dao.hpp>
#include <laurena/persistance/serial_manager.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*     persistance engine                                                       */ 
/********************************************************************************/ 


class persistance
{
public:

    /****************************************************************************/
    /*          constants                                                       */ 
    /****************************************************************************/
    enum SELECTOR : word8
    {
        PRIMARY_KEY = 0,
        SERIAL_KEY  = 1
    };


    void add(const std::string& pipeline, dao::sptr pdao);
    void add (const std::string& pipeline, serial_manager::sptr pserial);

    /****************************************************************************/ 
    /*          persistance functions                                           */ 
    /****************************************************************************/ 
    void insert(const std::string& pipeline, any object);

    void select(const std::string& pipeline, const any& key, any destination, persistance::SELECTOR = PRIMARY_KEY);


    bool exist(const std::string& pipeline, const any& primaryKey);

    void select_by_primary_key(const std::string& pipeline, const any& primaryKey, any& destination);
    void select_by_serial_key(const std::string& pipeline, const any& serialKey, any& destination);
    any  serial_to_object (const std::string& pipeline, const std::string& key);

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    std::unordered_map<std::string, dao::sptr>              _daos;
    std::unordered_map<std::string, serial_manager::sptr>   _serial_managers;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file