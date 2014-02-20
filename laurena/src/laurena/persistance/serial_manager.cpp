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

serial_manager::serial_manager(const std::string& spipeline) : _pipeline(spipeline), _last_serial(SERIAL_UNDEFINED)
{ }

serial_manager::serial_manager(const char* spipeline) : _pipeline(spipeline), _last_serial(SERIAL_UNDEFINED)
{ }

serial_manager::~serial_manager()
{ }

// USeless ?
bool serial_manager::remove_object(any object)
{
    const descriptor* d = object.desc();
    any serial_value;
    d->serial().get(object, serial_value);
    return this->remove(serial_value.tos());
}

word64 serial_manager::new_serial()
{
    if (this->_last_serial == SERIAL_UNDEFINED)
    {
        this->load_last_serial();
        assert(this->_last_serial != SERIAL_UNDEFINED);
    }

    ++this->_last_serial;
    this->save_last_serial();
    return this->_last_serial;
}

bool serial_manager::is_valid_serial(const std::string& serialKey)
{
    if (serialKey == "")
        return false;
    
    return boost::lexical_cast<word64>(serialKey) > 0;
}

//End of file
