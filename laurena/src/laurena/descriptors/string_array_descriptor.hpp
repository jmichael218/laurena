///
/// \file     string_array_descriptor.hpp
/// \brief    descriptors for class string_array
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for class string_array
///

#ifndef LAURENA_STRING_ARRAY_DESCRIPTOR_H
#define LAURENA_STRING_ARRAY_DESCRIPTOR_H

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
#include <laurena/types/string_array.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/descriptors/vector_descriptor.hpp>
#include <laurena/descriptors/string_descriptor.hpp>
#include <laurena/traits/laurena_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          string_array_descriptor                                              */ 
/*********************************************************************************/ 

class string_array_descriptor : public vector_descriptor<string_array,std::string> 
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    string_array_descriptor();

};


template<> 
struct td<string_array>
{
    static const descriptor* desc();
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif