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
    if (p->serial())
        value = p->serial();
    else 
        value = std::string("");
}

void setter_unique_owner(any& obj, const any& value)
{
    unique* p = anycast<unique*>(obj);
    word64  s = anycast<word64>(value);
    p->owner(s);
}

void getter_unique_owner(const any& obj, any& value)
{
    unique* p = anycast<unique*>(obj);
    unique::sptr spowner = p->owner();
    value = (spowner == nullptr) ? unique::UNDEFINED_SERIAL : spowner->serial() ;
}


const descriptor* td<unique>::desc()
{
    static standard_class_descriptor<unique>* res = nullptr;
    if (res == nullptr)
    {
        res = standard_class_descriptor<unique>::build("unique");       
		res->add_field<word64>("serial", setter_unique_serial, getter_unique_serial);
        res->add_field<word64>("owner",  setter_unique_owner, getter_unique_owner);
        res->serialKeyField("serial");
    }

    return res;
}
