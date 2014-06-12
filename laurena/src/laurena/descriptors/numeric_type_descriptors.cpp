///
/// \file     numeric_type_descriptors.cpp
/// \brief    int and other number types descriptor template
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// int and other number types descriptor template
///

#include <laurena/descriptors/numeric_type_descriptors.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>

using namespace laurena;

/********************************************************************************/ 
/*      code for class word8_type_descriptor                                    */ 
/********************************************************************************/
// CONSTRUCTOR
word8_type_descriptor::word8_type_descriptor () : numeric_type_descriptor<word8>("word8")
{}

// TO/FROM STRING SERIALIZATION 
std::string word8_type_descriptor::atos(const any& value) const
{
    word16 t = anycast<word8>(value);
    return lexical_cast<std::string,word16>(t);
}

any& word8_type_descriptor::stoa(const std::string& string_value, any& value) const
{
    word16 t = lexical_cast<word16,std::string>(string_value);
    if (t > 255)
        throw new LAURENA_FAILED_PARSING_EXCEPTION("value is out of bounds",string_value);
    return value = (word8)t;
}

/********************************************************************************/ 
/*      code for class int8_type_descriptor                                     */ 
/********************************************************************************/
// CONSTRUCTOR
int8_type_descriptor::int8_type_descriptor () : numeric_type_descriptor<int8>("int8")
{}

// TO/FROM STRING SERIALIZATION 
std::string int8_type_descriptor::atos(const any& value) const
{
    int16 t = anycast<int8>(value);
    return lexical_cast<std::string,int16>(t);
}

any& int8_type_descriptor:: stoa(const std::string& string_value, any& value) const
{
    int16 t = lexical_cast<int16,std::string>(string_value);
       if ( t < SCHAR_MIN || t > SCHAR_MAX )
        throw new LAURENA_FAILED_PARSING_EXCEPTION("value is out of bounds",string_value);
    return value = (int8)t;
}
//End of file