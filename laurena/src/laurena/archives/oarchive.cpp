///
/// \file     oarchive.cpp
/// \brief    Base class for an output archive i.e a class to serialize a class into a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an output archive i.e a class to serialize a class into a file format.
///

#include <laurena/archives/oarchive.hpp>

using namespace laurena;


oarchive::oarchive () : _data(), _logger(NULL)
{ 
}

oarchive::~oarchive ()
{
}

oarchive& oarchive::clear ()
{  
  
    this->_data.str("") ;
    this->_data.clear();
    return *this;
}

//End of file

