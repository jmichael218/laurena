/// \file     descriptable.cpp
/// \brief    A base class for descriptable types (class, field members, functions, methods)
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A base class for descriptable types (class, field members, functions, methods)
///
#include <laurena/descriptors/descriptable.hpp>
#include <laurena/exceptions/exception.hpp>

using namespace laurena;

descriptable::descriptable (const char* name) : _name (name) , _annotations ()
{ 
	this->_annotations._own_annotations = true;
}

descriptable::~descriptable ()
{ }

descriptable& descriptable::annotate(annotation* ptrvalue)
{ 
	this->_annotations [ ptrvalue->name () ] = ptrvalue ; 

	ptrvalue->_descriptable = this;
	if (!ptrvalue->acceptDescriptable())
	{
		ptrvalue->acceptDescriptable();
		throw LAURENA_EXCEPTION ("Can't set this annotation on this class of descriptable.");

	}
	ptrvalue->annotated();

	return *this ; 
}

//End of file

