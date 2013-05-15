///
/// \file     keymapper_feature.h
/// \brief    Extra Interface for containers : allow to map a key value to another. 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Extra Interface for containers : allow to map a key value to another. 
/// Exemple for a vector<string> 0 => english, 1 => french, 2=> italian
/// So english = "hello" will be the same as 0 = english.
///
#ifndef LAURENA_KEY_MAPPER_FEATURE_H
#define LAURENA_KEY_MAPPER_FEATURE_H

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
#include <laurena/traits/laurena_traits.hpp>
#include <laurena/descriptors/features/class_feature.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          keymapper_feature                                                */ 
/*********************************************************************************/ 
class keymapper_feature : public class_feature
{
public:


    keymapper_feature(const descriptor* desc) : class_feature(desc) {};
    virtual ~keymapper_feature () {}

    /****************************************************************************/ 
    /*          any-typed   class functions                                     */ 
    /****************************************************************************/ 
    virtual bool map (const any& object, const any& key, any& value) const = 0;
    virtual bool find (const any& object, any& key, const any& value) const = 0;
     
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
