///
/// \file     classs_features.hpp
/// \brief    core class features enum
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// core class features enum
///
#ifndef LAURENA_CLASS_FEATURES_H
#define LAURENA_CLASS_FEATURES_H

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
/*          descriptor                                                      */ 
/*********************************************************************************/ 
enum class Feature
{
        POLYMORPHIC,
        ANY,
        CONTAINER,
        KEY_MAPPER,
        VALUE_FORMAT_MDL,   
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
