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

unique::unique () : _serial (UNDEFINED_SERIAL), _owner_serial(UNDEFINED_SERIAL), _owner()
{ }

unique::unique (word64 serial) : _serial (serial), _owner_serial(UNDEFINED_SERIAL), _owner()
{ }

unique::unique (const unique& u) : _serial(u._serial), _owner_serial(u._owner_serial), _owner(u._owner)
{ }

unique::unique (unique&& u) : _serial(u._serial), _owner_serial(u._owner_serial), _owner(u._owner)
{ }

unique::~unique()
{ }

void unique::owner(unique::sptr& ptr)
{
    this->_owner = ptr;
    this->_owner_serial =  (ptr == nullptr) ? UNDEFINED_SERIAL : ptr->serial();
}

void unique::owner(word64 value)
{    
    this->_owner_serial = value; 
    if (value == UNDEFINED_SERIAL)
        this->_owner.reset();
    else
        if (!this->_owner.expired())
        {
            sptr p = this->_owner.lock();
            if (p->serial() != value)
                this->_owner.reset();
        }
}
//End of file
