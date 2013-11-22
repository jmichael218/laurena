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
/*         code for string_array_descriptor                                    */ 
/*                                                                              */ 
/********************************************************************************/ 
string_array_descriptor::string_array_descriptor() : vector_descriptor<string_array,std::string>("stringArray")
{ }

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