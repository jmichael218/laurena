///
/// \file     bitset_descriptor.cpp
/// \brief    A special class descriptor for boost::dynamic_bitset
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable class composed of serializable fields 
///
#include <laurena/descriptors/bitset_descriptor.hpp>
#include <laurena/toolboxes/bitset.hpp>
#include <laurena/types/any.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*              CODE FOR CLASS bitset_descriptor                                */ 
/*                                                                              */ 
/********************************************************************************/ 

// CONSTRUCTOR
bitset_descriptor::bitset_descriptor () : descriptor("bitset",typeid(boost::dynamic_bitset<>))
{
}

//ACCESSORS
any& bitset_descriptor::clear(any& value) const
{
    boost::dynamic_bitset<>* p = anycast<boost::dynamic_bitset<>*>(value);
    p->clear();
    return value;
}

bool bitset_descriptor::has(descriptor::Flags flag) const
{
	if (flag == Flags::STRING_CAST)
		return true;
	return this->descriptor::has(flag);
}

//CAST
any& bitset_descriptor::cast (any& value) const
{
	if (value.desc() != this)
	{
		std::string svalue; 
		this->fromString(value,value.desc()->toString(value,svalue));
	}

	return value;
}

// OPERATORS
bool bitset_descriptor::equals(const any& a0, const any& a1) const
{
	return (anycast<boost::dynamic_bitset<>*>(a0)) == (anycast<boost::dynamic_bitset<>*>(a1));
}

// RAW VALUE SERIALIZATION
void bitset_descriptor::set(void* ptr, const any& value)  const
{
	boost::dynamic_bitset<>* destination = (boost::dynamic_bitset<>*) ptr; 
	if (value.desc() != this)	
    {
        any a = destination;
        std::string svalue;
        this->fromString(a,value.desc()->toString(value,svalue));
    }

    *destination = *anycast<boost::dynamic_bitset<>*>(value);
}

any& bitset_descriptor::get(void* ptr, any& value)  const
{
    boost::dynamic_bitset<>* t = (boost::dynamic_bitset<>*) ptr;
    return value = t;   
}

// TO/FROM STRING SERIALIZATION
std::string& bitset_descriptor::toString(const any& value, std::string& destination) const
{
    boost::dynamic_bitset<>* p = anycast<boost::dynamic_bitset<>*>(value);
    return bitset::toString(*p,destination);
}

any& bitset_descriptor::fromString(any& value, const std::string& string_value) const
{
    boost::dynamic_bitset<>* p = anycast<boost::dynamic_bitset<>*>(value);
    bitset::parse(*p,string_value);
    return value;
}    

// OBJECT CONSTRUCTOR FOR INJECTION
any& bitset_descriptor::create(any& destination) const
{
    return 	destination = new boost::dynamic_bitset<> ();
}

/********************************************************************************/ 
/*                                                                              */ 
/*              CODE FOR CLASS td<bitset_descriptor>                            */ 
/*                                                                              */ 
/********************************************************************************/ 

const descriptor* td<boost::dynamic_bitset<> >::desc()
{
    static const descriptor* res = NULL;
    if (res == NULL)
    {
        res = new bitset_descriptor();
        classes::add(res);
    }
    return res;
}

//end of file
