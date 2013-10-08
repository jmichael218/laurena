///
/// \file     stdstream.cpp
/// \brief    A toolbox of functions on std::istream and std::ostream classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A toolbox of functions on std::istream and std::ostream classes

#include <laurena/toolboxes/stdstream.hpp>
#include <laurena/constants/const_charsets.hpp>


using namespace laurena;

word32 Stream::skipWhile(std::istream& stream, const charset<>& characters)
{
    word32 res = 0;
    if (stream.eof())
        return 0;
    while (characters.test((word8)stream.peek()))
    {
        res++;
        stream.ignore(1);

        if (stream.eof())
            break;
    }
    return res;
}


word32 Stream::skipUntil(std::istream& stream, const charset<>& characters)
{
    word32 res = 0;
    if (stream.eof())
        return 0;

    while (!characters.test((word8)stream.peek()))
    {
        res++;
        stream.ignore(1);

        if (stream.eof())
            break;
    }
    return res;
}

word32 Stream::readWhile(std::istream& stream, const charset<>& characters, std::string& destination)
{
    
    word32 res = 0;
    std::stringbuf buf;

    while (true)
    {
        if (stream.eof())
            break;

        char c = stream.peek();

        if (c == -1)
            break;

        if (characters.test((word8)c) == false)
            break;

        buf.sputc(c);
        stream.ignore(1);
        res ++;
    }

    destination = buf.str();
    return res;
    
}


word32 Stream::readUntil(std::istream& stream, const word8 symbol, std::string& destination)
{
    word32 res = 0;
    std::stringbuf buf;

    while (true)
    {
        if (stream.eof())
            break;

        char c = stream.peek();

        if (c == -1)
            break;

        if (c == symbol)
            break;

        buf.sputc(c);
        stream.ignore(1);
        res ++;
    }

    destination = buf.str();
    return res;
        
}

word32 Stream::readUntil(std::istream& stream, const charset<>& characters, std::string& destination)
{
word32 res = 0;
std::stringbuf buf;
char c;

    while (true)
    {
        if (stream.eof())
            break;

        c = stream.peek();
        if ( c == -1)
            break;

        if (characters.test((word8)c) == true)
            break;

        buf.sputc(c);
        stream.ignore(1);
        res ++;
    }

    destination = buf.str();
    return res;
}

bool Stream::expect(std::istream& stream, const char* expected)
{
char c;
    while (*expected && !stream.eof())
    {
        c = stream.peek();
        if (c == -1 )
            break;

        if (c != *expected)
            return false;

        expected++;
        stream.ignore(1);
    }
    return (*expected) == 0;
}
//End of file

