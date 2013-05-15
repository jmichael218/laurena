///
/// \file     list_descriptor.cpp
/// \brief    Describe a serializable std::list<T> class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable std::list<T> class
///

#include <laurena/descriptors/list_descriptor.hpp>
#include <laurena/exceptions/exception.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*      code for class base_list_container_feature                              */ 
/*                                                                              */ 
/********************************************************************************/ 
base_list_container_feature::base_list_container_feature(const descriptor* cd, const descriptor* elementDescriptor, bool areElementsPointer) : 

    container_feature(cd), _elements_descriptor(elementDescriptor) , _are_elements_pointer(areElementsPointer)
    

{}


bool base_list_container_feature::hasKey() const
{
    return false;
}

const descriptor* base_list_container_feature::elementDescriptor()    const
{
    return this->_elements_descriptor;
}

const descriptor* base_list_container_feature::keyDescriptor()         const
{
    return nullptr;
}

bool base_list_container_feature::areElementsPointers()            const
{
    return this->_are_elements_pointer;
}

void base_list_container_feature::set(any& container, const any& key, any& element) const
{
    throw LAURENA_EXCEPTION("You can't call this function on a container without keyed index." );
}

void base_list_container_feature::get(any& container, const any& key, any& element) const
{
    throw LAURENA_EXCEPTION("You can't call this function on a container without keyed index." );
}

//End of file