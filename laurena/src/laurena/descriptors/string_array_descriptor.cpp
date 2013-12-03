///
/// \file     string_array_descriptor.cpp
/// \brief    descriptors for class string_array
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for class string_array
///

#include <laurena/descriptors/string_array_descriptor.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*         code for string_array_keymapper_feature                              */ 
/*                                                                              */ 
/********************************************************************************/ 
string_array_keymapper_feature::string_array_keymapper_feature(const descriptor* d) : keymapper_feature(d)
{ }

string_array_keymapper_feature::~string_array_keymapper_feature()
{ }

bool string_array_keymapper_feature::map (const any& object, const any& key, any& value) const 
{
	string_array* sa = anycast<string_array*>(object);
	if (sa->attributes() == nullptr)
		value = key;
	else
	{
		word32 index = anycast<word32>(key);
		value = sa->attributes()->operator[](index);
	}
	return true;
}
    
bool string_array_keymapper_feature::find (const any& object, any& key, const any& value) const
{
	string_array* sa = anycast<string_array*>(object);
	if (sa->attributes() == nullptr)
		key = value;
	else
	{
		std::string s = anycast<std::string>(value);
		auto i = sa->attributes()->findExact(s);
		if (i == -1)
			key = value;
		else
			key = (word32) i;
	}     
	return true;
}


/********************************************************************************/ 
/*                                                                              */ 
/*         code for string_array_descriptor                                     */ 
/*                                                                              */ 
/********************************************************************************/ 
string_array_descriptor::string_array_descriptor() : vector_descriptor<string_array,std::string>("stringArray")
{ }

const class_feature*   string_array_descriptor::feature(Feature featureId) const
{
static string_array_keymapper_feature f(this);

	if (featureId == Feature::KEY_MAPPER)
		return &f;

	return this->vector_descriptor<string_array, std::string>::feature(featureId);
}

any& string_array_descriptor::getFieldValue(const any& ptr, const std::string& attribute_name,any& value) const
{
	const string_array* psa = anycast<const string_array*>(ptr);
	int index = (psa->attributes() == nullptr) ?  -1 : psa->attributes()->find(attribute_name);
	if (index == -1)
		return this->vector_descriptor<string_array,std::string>::getFieldValue(ptr, attribute_name, value);
	return value = psa->operator[](index);
}

/********************************************************************************/ 
/*                                                                              */ 
/*         code for td<string_array>                                            */ 
/*                                                                              */ 
/********************************************************************************/ 


const descriptor* td<string_array>::desc()
{
    static string_array_descriptor* res = nullptr;
    if (res == NULL)
    {
        res = new string_array_descriptor();
        classes::add(res);

		// getter for the vector size
		field::getter getsize = [] (const any& object, any& value) { string_array* c = anycast<string_array*>(object); value = c->size(); };

		// setter for the vector size
		field::setter setsize = [] (any& object, const any& value) { string_array* b = anycast<string_array*>(object); b->resize(anycast<word32>(value));};

		res->init_virtual_field("size", word32, setsize, getsize).supportTag("vector.size");
    }

    return res;
}
//End of file