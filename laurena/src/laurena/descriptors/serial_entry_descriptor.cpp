///
/// \file     serial_entry_descriptor.cpp
/// \brief    descriptor for class serial_entry
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptor for class serial_entry
///
#include <laurena/descriptors/serial_entry_descriptor.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>

using namespace laurena;

const descriptor* td<serial_entry>::desc()
{
    static standard_class_descriptor<serial_entry>* res = nullptr;
    if (res == nullptr)
    {
        res = standard_class_descriptor<serial_entry>::build("serial_entry");       
        res->add_field(&serial_entry::_serial,"serial");
        res->add_field(&serial_entry::_pipeline,"persistance");
        res->add_field(&serial_entry::_primary_key,"key");
        res->add_field(&serial_entry::_descriptor_name,"class");
    }

    return res;
}
