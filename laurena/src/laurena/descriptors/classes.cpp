///
/// \file     classes.cpp
/// \brief    Manager of serializable classes descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Manager of serializable classes descriptors
///
#include <laurena/descriptors/classes.hpp>
#include <laurena/debug/debug.hpp>
#include <laurena/descriptors/features/polymorphic_feature.hpp>
#include <laurena/descriptors/features/class_features.hpp>

#include <laurena/descriptors/string_descriptor.hpp>
#include <laurena/descriptors/numeric_type_descriptors.hpp>
#include <laurena/descriptors/variable_descriptor.hpp>
#include <laurena/descriptors/any_descriptor.hpp>
#include <laurena/descriptors/string_array_descriptor.hpp>
#include <laurena/descriptors/bitset_descriptor.hpp>
#include <laurena/descriptors/const_ptr_descriptor_descriptor.hpp>
#include <laurena/descriptors/parameter_descriptor.hpp>

#include <laurena/exceptions/exception.hpp>

using namespace laurena;

std::unordered_map<std::string,const descriptor*>      classes::_classes_by_name;
std::unordered_map<std::type_index,const descriptor*>           classes::_classes_by_typeid;

void classes::add(const descriptor* myClass)
{
    _classes_by_name[myClass->name()] = myClass;
    _classes_by_typeid[std::type_index(myClass->type())] = myClass;
}

const descriptor*  classes::byName(const std::string& name)
{
	auto i = classes::_classes_by_name.find(name);
	return i == classes::_classes_by_name.end () ? nullptr : i->second;    
}

const descriptor*  classes::byType(const type_info& type)
{
    auto i = classes::_classes_by_typeid.find(std::type_index(type));
	return i == classes::_classes_by_typeid.end () ? nullptr : i->second;  
}

void classes::logClasses (std::ostream& destination)
{
	for (auto p : classes::_classes_by_typeid)
		destination << p.second->name() << " ";	
}

bool classes::areParents(const descriptor& c1, const descriptor& c2)
{
    if (c1.type() == c2.type())
        return true;

    const polymorphic_feature* pcf1 = dynamic_cast<const polymorphic_feature*>(c1.feature(Feature::POLYMORPHIC));
    const polymorphic_feature* pcf2 = dynamic_cast<const polymorphic_feature*>(c2.feature(Feature::POLYMORPHIC));



    return ( pcf1!= NULL && pcf2 != NULL ) ? ( pcf1->isParentClass(c2) || pcf2->isParentClass(c1)) : false ;
}

void classes::errorTypeNotFound(const type_info& type)
{
	std::ostringstream ss;
	ss << "No class descriptor found for type " << type.name();
	throw LAURENA_EXCEPTION(ss.str());
}

void classes::init ()
{
    // std::string descriptor stored
    td<std::string>::desc();

    // numeric types
    td<word8>::desc();
    td<int8>::desc();
	
    td<word16>::desc();
    td<int16>::desc();
    td<word32>::desc();
    td<int32>::desc();
    td<word64>::desc();
    td<int64>::desc();

    // types descriptors
	td<const descriptor *>::desc();
    td<any>::desc();
    td<variable>::desc();
    td<variable_list>::desc();
    td<string_array>::desc();
    td<boost::dynamic_bitset<>>::desc();
	td<parameter>::desc();
	td<parameters>::desc();

}

//end of file
