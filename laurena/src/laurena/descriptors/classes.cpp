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

using namespace laurena;

std::unordered_map<std::string,const descriptor*>      classes::_classes_by_name;
std::unordered_map<word64,const descriptor*>           classes::_classes_by_typeid;

void classes::add(const descriptor* myClass)
{
    _classes_by_name[myClass->name()] = myClass;
    _classes_by_typeid[(word64)&myClass->type()] = myClass;
}

const descriptor*  classes::byName(const std::string& name)
{
    return _classes_by_name [name];
}

const descriptor*  classes::byType(const type_info& type)
{
    #ifdef LAURENA_DEBUG_CLASSES
        const descriptor* res = _classes_by_typeid[(word64)&type];
        if (!res)
        {
            std::string msg = "In classes::byType, failed to find class ";
            msg.append(type.name());
            debug::println(msg);
            assert(false);
        }
        return res;
    #else
        return _classes_by_typeid[(word64)&type];
    #endif
    
}

void classes::logClasses ()
{

}

bool classes::areParents(const descriptor& c1, const descriptor& c2)
{
    if (c1.type() == c2.type())
        return true;

    const polymorphic_feature* pcf1 = dynamic_cast<const polymorphic_feature*>(c1.feature(Feature::POLYMORPHIC));
    const polymorphic_feature* pcf2 = dynamic_cast<const polymorphic_feature*>(c2.feature(Feature::POLYMORPHIC));



    return ( pcf1!= NULL && pcf2 != NULL ) ? ( pcf1->isParentClass(c2) || pcf2->isParentClass(c1)) : false ;
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
    td<any>::desc();
    td<variable>::desc();
    td<variable_list>::desc();
    td<string_array>::desc();
    td<boost::dynamic_bitset<>>::desc();

}

//end of file
