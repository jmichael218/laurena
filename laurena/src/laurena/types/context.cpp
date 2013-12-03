///
/// \file     context.cpp
/// \brief    A context is a collection of variables
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A context is a collection of variables
///
#include <laurena/types/context.hpp>

using namespace laurena;

variable* context::get(const std::string& name)
{
	auto it = this->find(name);
	return (it == this->end()) ? nullptr : &it->second;
}

context&  context::push(const std::string& name, any value)
{
	variable& v = this->operator[](name);
	v._name = name;
	v._value = value;
	return *this;
}
//End of files
