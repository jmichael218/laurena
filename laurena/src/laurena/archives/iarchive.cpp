///
/// \file     iarchive.cpp
/// \brief    Base class for an input archive i.e a class to serialize a class from a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an input archive i.e a class to serialize a class from a file format.
///

#include <laurena/archives/iarchive.hpp>

using namespace laurena;

//! Default constructor
iarchive::iarchive () : _logger(nullptr), _source_filename (), _data ()
{ }

//! destructor
iarchive::~iarchive()
{ }

iarchive& iarchive::clear ()
{
    this->_source_filename = "";
    this->_data.str("");
    return *this;
}

//End of file

