///
/// \file     unique.cpp
/// \brief    A base type to be used as base class for classes bases on the same serial table
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A base type to be used as base class for classes bases on the same serial table
///
#include <laurena/types/unique.hpp>

using namespace laurena;

unique::unique () : _serial (UNDEFINED_SERIAL)
{ }

unique::unique (word64 serial) : _serial (serial)
{ }

unique::unique (const unique& u) : _serial(u._serial)
{ }

unique::unique (unique&& u) : _serial(u._serial)
{ }

unique::~unique()
{ }

word64 unique::serial() const
{ return this->_serial; }


void unique::serial(word64 value)
{ this->_serial = value; }

//End of file
