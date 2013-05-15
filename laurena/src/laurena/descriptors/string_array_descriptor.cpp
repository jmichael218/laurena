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
    static const string_array_descriptor* res = NULL;
    if (res == NULL)
    {
        res = new string_array_descriptor();
        classes::add(res);
    }

    return res;
}
//End of file