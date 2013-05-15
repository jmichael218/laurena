///
/// \file     stdstring.cpp
/// \brief    A toolbox of functions for std::string, mainly parsing functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for std::string, mainly parsing functions
///
#include <laurena/toolboxes/stdstring.hpp>
#include <laurena/constants/const_charsets.hpp>
#include <laurena/toolboxes/cstring.hpp>

using namespace laurena;

bool stdstring::isInteger(const std::string& str)
{
const char* p = str.c_str();

    if (*p == '-')
        ++p;    
    return CHARSET_NUMBER.validate(p);
}

bool stdstring::startWith(const std::string& str, const std::string& expected_prefix, bool caseSensitive)
{
    return cstring::startWith(str.c_str(),expected_prefix.c_str(),caseSensitive,expected_prefix.length());
}
//End of file
