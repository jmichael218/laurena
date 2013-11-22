///
/// \file     parameter_descriptor.hpp
/// \brief    descriptors for class parameter
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for class parameter
///

#ifndef LAURENA_PARAMETER_DESCRIPTOR_H
#define LAURENA_PARAMETER_DESCRIPTOR_H

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
#include <laurena/functions/parameter.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/traits/laurena_traits.hpp>

#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          string_array_descriptor                                              */ 
/*********************************************************************************/ 

template<> 
struct td<parameter>
{
    static const descriptor* desc();
};

template<>
struct td<parameters>
{
    static const descriptor* desc();
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif