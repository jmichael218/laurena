///
/// \file     charset.cpp
/// \brief    A dynamic_bitset boost set of bits enhanced to hold mask for character sets
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A dynamic_bitset boost set of bits enhanced to hold mask for character sets
///

#include <laurena/types/charset.hpp>

using namespace laurena;

charset::charset() : boost::dynamic_bitset<>(256)
{ }

charset::charset (const char* characters) : boost::dynamic_bitset<>(256)
{
    const word8* p = (word8*) characters;
    while (*p)
        this->set(*(p++)); 

    _characters = characters ;
}

charset::charset (const std::string& characters) : boost::dynamic_bitset<>(256)
{
    const word8* p = (word8*) characters.data();
    while (*p)
        this->set(*(p++));    

    _characters = characters;
}

bool charset::validate(const char* source, word32 size) const
{
    while (size && *source)
    {
        if (!this->test(*(source++)))
            return false;
        --size;
    }
    return true;
}

bool charset::validate(const std::string& source) const
{
    return this->validate(source.c_str(),source.length());
}
bool charset::validate(const word8* source, word32 size) const
{
    return this->validate((const char*)source,size);
}

//end of file
