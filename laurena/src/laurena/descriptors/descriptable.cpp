/// \file     descriptable.cpp
/// \brief    A base class for descriptable types (class, field members, functions, methods)
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A base class for descriptable types (class, field members, functions, methods)
///
#include <laurena/descriptors/descriptable.hpp>

using namespace laurena;

descriptable::descriptable (const char* name) : _name (name) , _annotations ()
{ 
	this->_annotations._own_annotations = true;
}

descriptable::~descriptable ()
{ }

//End of file

