///
/// \file     classs_feature.hpp
/// \brief    Implementation of a special feature for a class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Implementation of a special feature for a class
///
#ifndef LAURENA_CLASS_FEATURE_H
#define LAURENA_CLASS_FEATURE_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          base class for a class feature                                       */ 
/*********************************************************************************/ 
class class_feature 
{
public:

    /****************************************************************************/ 
    /*      constructor, destructors                                            */ 
    /****************************************************************************/ 
    class_feature(const descriptor* desc);
    virtual ~class_feature();

    /****************************************************************************/
    /*          accessors                                                       */ 
    /****************************************************************************/ 
    inline const descriptor& desc() const        { return *_descriptor;} 

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
protected:

    const descriptor*          _descriptor;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
