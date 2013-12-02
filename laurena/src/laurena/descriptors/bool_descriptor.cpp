///
/// \file     bool_descriptor.cpp
/// \brief    A special class descriptor for the bool type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A special class descriptor for the bool type
///
#include <laurena/descriptors/bool_descriptor.hpp>

using namespace laurena;


// CONSTRUCTOR
bool_descriptor::bool_descriptor () : descriptor("bool",typeid(bool))
{
}

//ACCESSORS
any& bool_descriptor::clear(any& value) const
{
	return value = false;
}

bool bool_descriptor::has(descriptor::Flags flag) const
{
	if (flag == Flags::NUMERIC_VALUE)
		return true;
	if (flag == Flags::TINY)
		return true;
	return this->descriptor::has(flag);
}

//CAST
any bool_descriptor::cast (const any& value) const
{
	if (value.desc() == this) 
		return anycast<bool>(value);
	
	if (value.desc()->type() == typeid(std::string))
	{
		any a (value);
		return this->stoa(value.tos(), a);
	}

	assert(false);
	
}

// OPERATORS
bool bool_descriptor::equals(const any& a0, const any& a1) const
{
	return anycast<bool>(a0) == anycast<bool>(a1);
}

// RAW VALUE SERIALIZATION
void bool_descriptor::set(void* ptr, const any& value)  const
{
	bool* destination = (bool*) ptr; 
	if (value.desc() != this)	
		*destination = anycast<bool>(this->cast(value));
	else
		*destination = anycast<bool>(value);
}

any& bool_descriptor::get(void* ptr, any& value)  const
{
    bool* t = (bool *) ptr;
    return value = *t;   
}

// TO/FROM STRING SERIALIZATION
std::string bool_descriptor::atos(const any& value) const
{
	bool b = anycast<bool>(value);
    return b ? "true" : "false" ;
}

any& bool_descriptor::stoa(const std::string& string_value, any& value) const
{
	if (string_value == "true")
		return  value = (bool) true;
	else if (string_value == "false")
		return value = (bool) false;
	else
		assert(false);
}    

// OBJECT CONSTRUCTOR FOR INJECTION
any bool_descriptor::create() const
{
    return  any(bool(true));
}

/********************************************************************************/ 
/*                                                                              */ 
/*              CODE FOR CLASS td<bitset_descriptor>                            */ 
/*                                                                              */ 
/********************************************************************************/ 

const descriptor* td<bool>::desc()
{
    static const bool_descriptor* res = NULL;
    if (res == NULL)
    {
        res = new bool_descriptor();
        classes::add(res);
    }
    return res;
}
//end of file
