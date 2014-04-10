///
/// \file     polymorphic_class_descriptor.hpp
/// \brief    Describe a serializable polymorphic class i.e derivated from or derivated of another class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe Describe a serializable polymorphic class i.e derivated from or derivated of another class
///

#ifndef LAURENA_POLYMORPHIC_CLASS_DESCRIPTOR_H
#define LAURENA_POLYMORPHIC_CLASS_DESCRIPTOR_H

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
#include <laurena/descriptors/features/polymorphic_feature.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          PolymorphicClassDescriptor                                           */ 
/*********************************************************************************/ 
class polymorphic_class_descriptor : public descriptor {
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    polymorphic_class_descriptor(const char* name, const type_info& type, size_t sizeOfObject, const descriptor* parent = nullptr);
    virtual ~polymorphic_class_descriptor();
    
   /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 

    // ACCESSORS  
    virtual const class_feature*      feature(Feature featureId) const;

    virtual size_t                      size_of() const;

    /****************************************************************************/ 
    /*          new functions                                                   */ 
    /****************************************************************************/         

    inline bool              has_parent () const    { return this->_polymorphic_class_feature.has_parent();}
    inline const descriptor& parent()     const     { return this->_polymorphic_class_feature.parent();}


    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    size_t                              _size_of;

    polymorphic_feature                 _polymorphic_class_feature;


};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif