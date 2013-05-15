///
/// \file     any_feature.h
/// \brief    Interface for class implementing or reimplementing the same features than class any. i.e a generic class container
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Interface for class implementing or reimplementing the same features than class any. i.e a generic class container
///
#ifndef LAURENA_ANY_CLASS_FEATURE_H
#define LAURENA_ANY_CLASS_FEATURE_H

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
#include <laurena/descriptors/features/class_feature.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          any_feature                                                  */ 
/*********************************************************************************/ 
class any_feature : public class_feature
{
public:

    //! constructor
    any_feature(const descriptor* desc) : class_feature(desc) {};
    virtual ~any_feature () {}

    /****************************************************************************/ 
    /*          any-typed   class functions                                     */ 
    /****************************************************************************/ 
    //!brief return true if the class is a generic class accepting any type of content, like boost::any
    virtual bool isAny () const =0;

    //!brief return the true type of the current content.
    virtual const descriptor& desc(void* ptrValue) const=0;

    //!brief return true if any content is empty
    virtual bool isEmpty (void* ptrValue) const =0;     
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
