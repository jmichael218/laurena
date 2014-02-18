///
/// \file     serial_manager.cpp
/// \brief    A base manager for a table of serial ID
/// \author   Frederic Manisse
/// \version  1.0
///
/// A base manager for a table of serial ID
///
#include <laurena/persistance/serial_manager.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/persistance/persistance.hpp>

using namespace laurena;

serial_manager::serial_manager(persistance& engine, const std::string& spipeline) : _persistance(engine), _pipeline(spipeline)
{ }

serial_manager::serial_manager(persistance& engine, const char* spipeline) : _persistance(engine), _pipeline(spipeline)
{ }

serial_manager::~serial_manager()
{ }


bool serial_manager::remove_object(any object)
{
    const descriptor* d = object.desc();
    any serial_value;
    d->serial().get(object, serial_value);
    return this->remove(serial_value);
}

//End of file
