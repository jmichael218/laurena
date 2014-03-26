///
/// \file     polymorphic_class_descriptor.h
/// \brief    Describe a serializable polymorphic class i.e derivated from or derivated of another class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe Describe a serializable polymorphic class i.e derivated from or derivated of another class
///

#include <laurena/descriptors/polymorphic_class_descriptor.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/descriptors/features/class_features.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*          constructors, destructor                                            */ 
/*                                                                              */ 
/********************************************************************************/ 
polymorphic_class_descriptor::polymorphic_class_descriptor(const char* name, const type_info& type, size_t sizeOfObject, const descriptor* parent)
                           :descriptor(name,type),
                            _size_of(sizeOfObject), _polymorphic_class_feature(this,parent)
{ }


polymorphic_class_descriptor::~polymorphic_class_descriptor()
{
/*
    if (this->_descriptor_identifier)
        delete this->_descriptor_identifier;    
*/ 
}

/********************************************************************************/ 
/*                                                                              */ 
/*              ACCESSORS                                                       */ 
/*                                                                              */ 
/********************************************************************************/ 
const class_feature* polymorphic_class_descriptor::feature(Feature featureId) const
{
	if ( (featureId == Feature::POLYMORPHIC) )
        return &this->_polymorphic_class_feature;

    return this->descriptor::feature(featureId);
}

size_t polymorphic_class_descriptor::size_of() const 
{
    return this->_size_of;
}


//end of file
