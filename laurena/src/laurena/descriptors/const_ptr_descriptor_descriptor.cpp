///
/// \file     const_ptr_descriptor_descriptor.cpp
/// \brief    A special class descriptor for the 'const descriptor*' type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A special class descriptor for the 'const descriptor*' type
///
#include <laurena/descriptors/const_ptr_descriptor_descriptor.hpp>
#include <laurena/descriptors/string_descriptor.hpp>

using namespace laurena;

/********************************************************************************/ 
/*																				*/ 
/*		code for class const_ptr_descriptor_descriptor							*/ 
/*																				*/ 
/********************************************************************************/ 
// CONSTRUCTOR
const_ptr_descriptor_descriptor::const_ptr_descriptor_descriptor () : descriptor("descriptor",typeid(const descriptor*))
{
}

//ACCESSORS
any& const_ptr_descriptor_descriptor::clear(any& value) const
{
	return value = (const descriptor*) nullptr;
}

bool const_ptr_descriptor_descriptor::has(descriptor::Flags flag) const
{
	if (flag == Flags::STRING_CAST)
		return true;
	if (flag == Flags::ATOMIC)
		return true;
	return this->descriptor::has(flag);
}

//CAST
any const_ptr_descriptor_descriptor::cast (const any& value) const
{
	return (value.desc() == this) ? value : any(value.tos());
}

// OPERATORS
bool const_ptr_descriptor_descriptor::equals(const any& a0, const any& a1) const
{
	return anycast<const descriptor*>(a0) == anycast<const descriptor*>(a1);
}

// RAW VALUE SERIALIZATION
void const_ptr_descriptor_descriptor::set(void* ptr, const any& value)  const
{
	const descriptor** destination = (const descriptor**) ptr; 
	if (value.desc() == td<std::string>::desc())
		*destination = classes::byName(anycast<std::string>(value));
	else
		*destination = anycast<const descriptor*>(value);
}

any& const_ptr_descriptor_descriptor::get(void* ptr, any& value)  const
{
    const descriptor* t = (const descriptor *) ptr;
    return value = t;   
}

// TO/FROM STRING SERIALIZATION
std::string const_ptr_descriptor_descriptor::atos(const any& value) const
{
	const descriptor* d = anycast<const descriptor*>(value);
    return d->name();
}

any& const_ptr_descriptor_descriptor::stoa(const std::string& string_value, any& value) const
{
    return value = classes::byName(string_value);
}    

// OBJECT CONSTRUCTOR FOR INJECTION
any const_ptr_descriptor_descriptor::create() const
{
    return  any((const descriptor*) nullptr);
}

/********************************************************************************/ 
/*																				*/ 
/*		code for class td<const descriptor*>									*/ 
/*																				*/ 
/********************************************************************************/ 

const descriptor* td<const descriptor*>::desc()
{
	static descriptor* res = nullptr;
	if (res == nullptr)
    {
		res = new const_ptr_descriptor_descriptor();
        classes::add(res);
    }
    return res;
};
//End of file