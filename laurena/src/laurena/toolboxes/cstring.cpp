///
/// \file     cstring.cpp
/// \brief    A toolbox of functions for old c string (or char*) , mainly parsing functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for old c string (or char*) , mainly parsing functions
///
#include <laurena/toolboxes/cstring.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

/*
bool cstring::startWith(const char* str, const char* expected_prefix, bool caseSensitive, word32 size)
{
    if (size == -1)
        size = strlen(expected_prefix);

    if(caseSensitive)
        return memcmp(str,expected_prefix,size) == 0;
    else
    {
        const char* s1 = str;
        const char* s2 = expected_prefix;

        while (size--)
        {
            if(UPPER(*s1) != UPPER(*s2))
                return false;

            ++s1;
            ++s2;
        }
        return true;
    }
}
*/

/*
std::string cstring::readWhile(const char* source, const charset<>& characters)
{
    word32 res = 0;
    const char* p = source;
    while(true)
    {
        if (characters.test((word8) (*p++)) == false)
            break; 

        ++res;              
    }
    return std::string(source,res);
}
*/

word32 cstring::readWhile(const char* source, std::string& destination, const charset<>& characters)
{
    word32 res = 0;
    const char* p = source;
    while(true)
    {
        if (characters.test((word8) (*p++)) == false)
            break; 

        ++res;              
    }
    destination.assign(source,res);
    return res;
}

std::string cstring::readUntil(const char* source, const charset<>& characters)
{
    word32 res = 0;
    while(true)
    {
        if (characters.test((word8) (*source++)))
            break; 

        ++res;              
    }
    return std::string(source,res);
}

word32 cstring::readUntil(const char* source, std::string& destination, const charset<>& characters)
{
    word32 res = 0;
    while(true)
    {
        if (characters.test((word8) (*source++)))
            break; 

        ++res;              
    }
    destination.assign(source,res);
    return res;
}

std::string cstring::readUntil(const char* source, const char character)
{
    word32 res = 0;
    const char* p = source;
    while(true)
    {
        if (!*p)
            break;

        if ( (*p++) ==  character)
            break; 

        ++res;
              
    }
    return std::string(source,res);
}

word32 cstring::readUntil(const char* source, std::string& destination, const char character)
{
    word32 res = 0;
    while(true)
    {
        if (!*source)
            break;

        if ( (*source++) ==  character)
            break; 

        ++res;
              
    }
    destination.assign(source,res);
    return res;
}

const char* cstring::skipWhile(const char* source, const charset<>& characters)
{
    while (characters.test(*source)) 
        source++;        
    return source;
}

word32 cstring::readInteger(const char* source, std::string& destination)
{
    bool isSigned = (*source == '-');    

    if (isSigned)
        source ++;    

    word32 readed = cstring::readWhile(source,destination,const_charsets<>::NUMBERS);

    if (isSigned && readed) 
    {
        destination.insert(0,"-");
        readed ++;
    }

    return readed;
}

//End of file