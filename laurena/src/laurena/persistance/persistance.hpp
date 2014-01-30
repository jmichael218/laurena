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

    void add(const std::string& pipeline, dao::sptr pdao);

    /****************************************************************************/ 
    /*          persistance functions                                           */ 
    /****************************************************************************/ 
    void create(const std::string& pipeline, any object);
    void read(const std::string& pipeline, const any& primaryKey, any destination);

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    std::unordered_map<std::string, dao::sptr>       _daos;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file