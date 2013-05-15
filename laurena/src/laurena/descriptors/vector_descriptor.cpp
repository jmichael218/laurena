///
/// \file     vector_descriptor.cpp
/// \brief    Describe a serializable std::vector<T> class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable std::vector<T> class
///

#include <laurena/descriptors/vector_descriptor.hpp>
#include <laurena/descriptors/numeric_type_descriptors.hpp>

using namespace laurena;


/********************************************************************************/ 
/*                                                                              */ 
/*      code for class base_list_container_feature                              */ 
/*                                                                              */ 
/********************************************************************************/ 
base_vector_container_feature::base_vector_container_feature(const descriptor* cd, const descriptor* elementDescriptor, bool areElementsPointer) : 

    container_feature(cd), _elements_descriptor(elementDescriptor) , _are_elements_pointer(areElementsPointer)
    

{}


bool base_vector_container_feature::hasKey() const
{
    return true;
}

const descriptor* base_vector_container_feature::elementDescriptor()    const
{
    return this->_elements_descriptor;
}

const descriptor* base_vector_container_feature::keyDescriptor()         const
{

    return td<word32>::desc();   ;
}

bool base_vector_container_feature::areElementsPointers()            const
{
    return this->_are_elements_pointer;
}

//End of file