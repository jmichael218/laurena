///
/// \file     file_location.hpp
/// \brief    A location in a file ( filename, column, line )
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A location in a file ( filename, column, line )
///

#include <laurena/parsing/file_location.hpp>
#include <laurena/debug/debug.hpp>

//#define DEBUG_FILE_PROCESS

using namespace laurena;

file_location::file_location () : _filename (), _column(0), _line(0)
{ }

file_location::file_location(const char* filename) : _filename (filename), _column(0), _line(0)
{ }

file_location::file_location(const std::string& filename) : _filename (filename), _column(0), _line(0)
{ }

void file_location::reset ()
{
    this-> _filename = "" ;
    this->_column = _line = 0;
}

void file_location::process (const char character)
{
    if (character == '\n' )
    {
        this->_line ++;
        this->_column = 0;
    }
    else
        this->_column ++;

    #ifdef DEBUG_FILE_PROCESS
        char cmsg[2] = "a";
        cmsg[0] = character;
        debug::println(cmsg);
    #endif

}

void file_location::process (const word8 character)
{
    if (character == '\n' )
    {
        this->_line ++;
        this->_column = 0;
    }
    else
        this->_column ++;

    #ifdef DEBUG_FILE_PROCESS
        char cmsg[2] = "a";
        cmsg[0] = character;
        debug::println(cmsg);
    #endif
}

void file_location::process (const char* ptr)
{
word8 c ;

    while (*ptr)
    {
        c = *ptr++;
        if (c == '\n') 
        {
            this->_line ++;
            this->_column = 0;
        }
        else
            this->_column ++;
    }

    #ifdef DEBUG_FILE_PROCESS       
        debug::println(ptr);
    #endif
}

void file_location::process (const char* ptr, word32 size)
{
word8 c ;

    size++;
    while (--size)
    {
        c = *ptr++;
        if (c == '\n') 
        {
            this->_line ++;
            this->_column = 0;
        }
        else
            this->_column ++;
    }
    #ifdef DEBUG_FILE_PROCESS       
        debug::println(ptr);
    #endif
}

void file_location::process(const std::string& content)
{
    this->process(content.c_str(),content.length());
    #ifdef DEBUG_FILE_PROCESS       
        debug::println(content);
    #endif
}



