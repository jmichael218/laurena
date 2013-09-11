///
/// \file       any.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      An extended version of boost::any with class descriptor info
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An extended version of boost::any with class descriptor info
///
#include <laurena/types/any.hpp>
#include <laurena/descriptors/string_descriptor.hpp>

using namespace laurena;

any::any()	: _content(nullptr)  {}

any::any(const char* str)        : _content(new content<std::string>(std::string(str),td<std::string>::desc())) {}

any::any(const any& other)       : _content(other._content ? other._content->clone() : 0) {}

any::any(any&& other)			 
{
	this->_content = other._content;
	other._content = nullptr;
}

any::~any()
{
	if (_content)
		delete _content;
}

any & any::operator=(const any& value)
{
	if (this->_content)
		delete _content;
    _content = value._content ? value._content->clone() : 0;
    return *this;
}

any& any::operator=(any&& value)
{
	if (_content)
		delete _content;
	_content = value._content;
	value._content = nullptr;
	return *this;
}

bool any::operator==(const any& value)
{
	if (_content)
    {
		const descriptor* cd   = this->desc();
        const descriptor* cd2  = value.desc();

        if (cd->has(descriptor::Flags::STRING_CAST) && cd2->has(descriptor::Flags::STRING_CAST))
        {
            return cd->atos(*this) == cd2->atos(value);
        }
        else
            return this->ptr() == value.ptr();
    }
    else
         return (value._content == nullptr);                     
}

std::string any::tos () const
{
	const descriptor* d = this->desc();
	return d ? d->atos(*this) : std::string();
}
//End of file
