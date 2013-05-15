///
/// \file     variable_descriptor.hpp
/// \brief    descriptors for classes variable and variable_list
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for classes variable and variable_list
///

#ifndef LAURENA_VARIABLE_DESCRIPTOR_H
#define LAURENA_VARIABLE_DESCRIPTOR_H

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
#include <laurena/types/variable.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/descriptors/list_descriptor.hpp>
#include <laurena/traits/laurena_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          variable_descriptor                                                  */ 
/*********************************************************************************/ 

class variable_descriptor : public standard_class_descriptor<variable>
{
public:    

    /****************************************************************************/ 
    /*          constructor, destructor                                         */ 
    /****************************************************************************/ 
    variable_descriptor  ();

};

template<> 
struct td<variable>
{
    static const descriptor* desc();
};

/*********************************************************************************/
/*          variable_list_descriptor                                             */ 
/*********************************************************************************/ 

class variable_list_descriptor : public list_descriptor<variable_list,variable> 
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    variable_list_descriptor();

};


template<> 
struct td<variable_list>
{
    static const descriptor* desc();
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif