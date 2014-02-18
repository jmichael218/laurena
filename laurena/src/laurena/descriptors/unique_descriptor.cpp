///
/// \file     variable_descriptor.cpp
/// \brief    descriptors for classes variable and variable_list
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for classes variable and variable_list
///
#include <laurena/descriptors/unique_descriptor.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>

using namespace laurena;

void setter_unique_serial(any& obj, const any& value)
{
    unique* p = anycast<unique*>(obj);
    word64  s = anycast<word64>(value);
    p->serial(s);
}

void getter_unique_serial(const any& obj, any& value)
{
    unique* p = anycast<unique*>(obj);
    value = p->serial();
}


const descriptor* td<unique>::desc()
{
    static standard_class_descriptor<unique>* res = nullptr;
    if (res == nullptr)
    {
        res = standard_class_descriptor<unique>::build("unique");       
		res->addField<word64>("serial", setter_unique_serial, getter_unique_serial);
        res->serialKeyField("serial");
    }

    return res;
}
