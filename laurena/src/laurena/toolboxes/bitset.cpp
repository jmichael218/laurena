///
/// \file     bitset.cpp
/// \brief    A toolbox of functions for boost:dynamic_bitset
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for boost:dynamic_bitset
///

#include <laurena/toolboxes/bitset.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;


std::string& bitset::serialize(const boost::dynamic_bitset<>& bits, const string_array& bitnames, std::string& destination, const std::string& separator)
{
    destination = "";
    bool first = true;
    for (word32 i = 0; i < bits.size(); ++i)
        if (bits.test(i))
        {
            if (first)
                first = false;
            else
                destination.append(separator);
            destination.append(bitnames[i]);
        }
    return destination;

}

std::string& bitset::serialize(word64 bits, const string_array& bitnames, std::string& destination, const std::string& separator)
{
    word64 mask = 1;
    destination = "";
    bool first = true;
    for (word32 i = 0; i < bitnames.size(); ++i)
    {
        if (bits & mask)
        {
            if (first)
                first = false;
            else
                destination.append(separator);
            destination.append(bitnames[i]);
        }
        mask <<= 1;
    }
    return destination;
    
}

std::string& bitset::serialize(const std::string& bits, const string_array& bitnames, std::string& destination, const std::string& separator)
{
    destination = "";
    bool first = true;
    const char* p = bits.c_str();
    char c ;
    for (word32 i = 0; i < bitnames.size(); ++i)
    {
        c = *(p++);
        if (c == '1')
        {
            if (first)
                first = false;
            else
                destination.append(separator);
            destination.append(bitnames[i]);
        }
    }
    return destination;
}


boost::dynamic_bitset<>& bitset::binary(boost::dynamic_bitset<>& bits, const std::string& binary)
{
    bits.resize(binary.length());
    const char* p = binary.c_str();
    char c;
    for (word32 i = 0 ; i < binary.length(); ++i)
    {
        c = *(p++);
        if ( c == '0')
            bits.set(i,false);
        else if ( c == '1' )
            bits.set(i);
        else
            throw LAURENA_FAILED_PARSING_EXCEPTION("In BitSet::parseBinary, source is not a [0-1]* regex" , binary.c_str()) ;   

    }
    return bits;
}


word64 bitset::parse(const string_array& bitnames, const charset& charset, const std::string& value )
{
    const char* p = value.c_str();
    char c;
    word32 i = 0;
    std::string key;
    word64 res = 0;
    while (*p)
    {
        c = *p;
        if (charset.test(c) == false)
        {
            ++p;
            continue;
        }

        i = 0;
        while (charset.test(p[i]))
            ++i;

        key.assign(p,i);
        int32 index = bitnames.find(key);
        if (index==-1)
        {
            throw LAURENA_FAILED_PARSING_EXCEPTION("In bitset::string, unknow flag" , key.c_str());
        }
        res += ((word64)1) << index;
        p +=i;

    }
    return res;
}

boost::dynamic_bitset<>& bitset::parse(boost::dynamic_bitset<>& destination, const string_array& bitnames, const charset& charset, const std::string& value)
{
const char* p = value.c_str();
char c;
word32 i = 0;
std::string key;

	if (destination.size() != bitnames.size())
		destination.resize(bitnames.size());

    while (*p)
    {
        c = *p;
        if (charset.test(c) == false)
        {
            ++p;
            continue;
        }

        i = 0;
        while (charset.test(p[i]))
            ++i;

        key.assign(p,i);
        int32 index = bitnames.find(key);
        if (index==-1)
        {
            throw LAURENA_FAILED_PARSING_EXCEPTION("In bitset::string, unknow flag" , key.c_str());
        }
        destination.set (index);
        p +=i;

    }
    return destination;
}

boost::dynamic_bitset<>& bitset::parse(boost::dynamic_bitset<>& destination, const std::string& value)
{
    destination.resize(value.length());
    destination.reset();
    
    const char* p = value.c_str();
    word32 index = 0;
    while (*p)    
        destination.set(index++,(*p++) == '0');

    return destination;
}

std::string& bitset::toString(const boost::dynamic_bitset<>& bits, std::string& destination)
{
    destination.assign (bits.size(),'0');
    if (bits.size() <= 0)    
        return destination;   

    for ( word32 i = 0 ; i < bits.size() ; i ++ )
        if ( bits.test(i))
            destination [i] = '1' ;

    return destination;
}
/*
word64 BitSet::toWord64 (const boost::dynamic_bitset<>& bits)
{
word64 res = 0 ;
word64 one = 1 ;
    for (word8 i = 0 ; i < bits.size() ; i ++)
        if ( bits.test(i))
            res |= ( one << i );

    return res;
}

boost::dynamic_bitset<>& BitSet::fromWord64 (word64 value, boost::dynamic_bitset<>& dest)
{
word64 one = 1 ;

    dest.clear();
    for (word8 i = 0 ; i < 64 ; i ++)
    {
        if ( value & ( one << i ))
            dest.set(i);       
    }
    return dest;
}
*/
//End of file
