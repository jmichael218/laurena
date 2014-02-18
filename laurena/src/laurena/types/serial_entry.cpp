///
/// \file     serial_entry.cpp
/// \brief    A class describing an entry for serial key managers
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A class describing an entry for serial key managers
///
#include <laurena/types/serial_entry.hpp>

using namespace laurena;

serial_entry::serial_entry() : _serial(), _pipeline(), _primary_key()
{ }

serial_entry::serial_entry(const serial_entry& s) : _serial(s._serial), _pipeline(s._pipeline), _primary_key(s._primary_key)
{ }

serial_entry::serial_entry(serial_entry&& s) : _serial(s._serial), _pipeline(s._pipeline), _primary_key(s._primary_key)
{ }

serial_entry::~serial_entry()
{ }

serial_entry& serial_entry::operator=(const serial_entry&  s)
{
    this->_serial = s._serial;
    this->_pipeline = s._pipeline;
    this->_primary_key = s._primary_key;
    return *this;
}

serial_entry& serial_entry::operator=(      serial_entry&& s)
{
    this->_serial = s._serial;
    this->_pipeline = s._pipeline;
    this->_primary_key = s._primary_key;
    return *this;
}
    
bool serial_entry::operator==(const std::string& s)
{
    return this->_serial == s;
}

bool serial_entry::operator==(const serial_entry& s)
{
    bool res = this->_serial == s._serial && this->_pipeline == s._pipeline;
    assert(this->_primary_key == s._primary_key);
    return res;
}

//End of file
