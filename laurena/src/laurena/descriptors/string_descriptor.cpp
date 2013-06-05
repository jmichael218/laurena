///
/// \file     string_descriptor.cpp
/// \brief    A special class descriptor for std::string
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A special class descriptor for std::string
///

#include <laurena/descriptors/string_descriptor.hpp>

using namespace laurena;

// CONSTRUCTOR
string_descriptor::string_descriptor () : descriptor("string",typeid(std::string))
{
}

//ACCESSORS
any& string_descriptor::clear(any& value) const
{
	return value = std::string("");
}

bool string_descriptor::has(descriptor::Flags flag) const
{
	if (flag == Flags::STRING_CAST)
		return true;
	if (flag == Flags::TINY)
		return true;
	return this->descriptor::has(flag);
}

//CAST
any& string_descriptor::cast (any& value) const
{
	if (value.desc() != this)
	{
		std::string svalue; 
		value = value.desc()->toString(value,svalue);
	}

	return value;
}

// OPERATORS
bool string_descriptor::equals(const any& a0, const any& a1) const
{
	return boost::equals(anycast<std::string>(a0),anycast<std::string>(a1));
}

// RAW VALUE SERIALIZATION
void string_descriptor::set(void* ptr, const any& value)  const
{
	std::string* destination = (std::string*) ptr; 
	if (value.desc() != this)	
		value.desc()->toString(value,*destination);
	else
		*destination = anycast<std::string>(value);
}

any& string_descriptor::get(void* ptr, any& value)  const
{
    std::string* t = (std::string *) ptr;
    return value = *t;   
}

// TO/FROM STRING SERIALIZATION
std::string& string_descriptor::toString(const any& value, std::string& destination) const
{
    return destination = anycast<std::string>(value);
}

any& string_descriptor::fromString(any& value, const std::string& string_value) const
{
    return value = string_value;
}    

// OBJECT CONSTRUCTOR FOR INJECTION
any& string_descriptor::create(any& destination) const
{
    return 	destination = std::string("");
}

//end of file
