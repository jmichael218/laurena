///
/// \file     polymorphic_feature.h
/// \brief    Interface of a polymorphic feature for a class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Interface of a polymorphic feature for a class
///
#ifndef LAURENA_POLYMORPHIC_CLASS_FEATURE_H
#define LAURENA_POLYMORPHIC_CLASS_FEATURE_H

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
/*          polymorphic_feature                                                  */ 
/*********************************************************************************/ 
class polymorphic_feature : public class_feature
{
public:


    polymorphic_feature(const descriptor* desc, const descriptor* parentDescriptor);
    virtual ~polymorphic_feature();

    /****************************************************************************/ 
    /*          polymorphic class functions                                     */ 
    /****************************************************************************/ 
    virtual bool hasParent () const;
    virtual const descriptor& parent() const;

    ///
    /// \brief return true if 'this' is a parent class of child_class
    ///
    virtual bool isParentClass(const descriptor& child_class) const;

    virtual void addChildClass (const descriptor* child_class);

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

        const descriptor*                  _parent;
        std::list<const descriptor*>*    _children;
     
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
