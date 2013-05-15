///
/// \file     container_feature.hpp
/// \brief    Interface of a container feature for a class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Interface of a container feature for a class
///
#ifndef LAURENA_CONTAINER_FEATURE_H
#define LAURENA_CONTAINER_FEATURE_H

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

#include <laurena/types/literator.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          container_feature                                                    */ 
/*********************************************************************************/ 
class container_feature : public class_feature
{
public:


    container_feature(const descriptor* desc) : class_feature(desc) {};
    virtual ~container_feature() {}

    /****************************************************************************/ 
    /*          any-typed   class functions                                     */ 
    /****************************************************************************/ 
    virtual bool                   hasKey()                const =0;

    virtual const descriptor*      elementDescriptor()     const =0;
    virtual const descriptor*      keyDescriptor()         const =0;

    virtual literator              begin(const any& container)    const=0;
    virtual literator              end(const any& container)      const=0;
    
	virtual bool				   areElementsPointers()          const=0;

    virtual void                   push(any& container, any& element) const =0;  // for non keyed container
    virtual void                   set(any& container, const any& key, any& element) const =0; // for keyed container
    virtual void                   get(any& container, const any& key, any& element) const =0;
     
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
