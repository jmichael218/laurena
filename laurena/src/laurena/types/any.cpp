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

//End of file
