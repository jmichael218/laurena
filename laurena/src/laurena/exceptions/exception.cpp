///
/// \file     exception.cpp
/// \copyright (C) Copyright 2002-2012 Frederic Manisse
/// \brief    The base exception for all exception of the library
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// The base exception for all exception of the library
///

/********************************************************************************/ 
/*              includes                                                        */ 
/********************************************************************************/ 
#include <laurena/exceptions/exception.hpp>
#include <laurena/debug/debug.hpp>

/********************************************************************************/ 
/*              namespaces                                                      */ 
/********************************************************************************/ 
using namespace laurena;

/********************************************************************************/ 
/*              implementation of constructors                                  */ 
/********************************************************************************/ 
exception::exception (const char* message, const char* filename, word32 line) 
                    
    : _message (message) , _filename (filename) , _line(line)

{
    this->ready();
}

exception::exception (const std::string& message, const char* filename, word32 line)

    : _message (message) , _filename (filename) , _line(line)

{
    this->ready();
}

exception::exception (const std::ostringstream& message, const char* filename, word32 line)

    : _message (message.str()) , _filename (filename) , _line(line)

{
    this->ready();
}

/********************************************************************************/ 
/*              destructor                                                      */ 
/********************************************************************************/ 
exception::~exception()
{}


/********************************************************************************/ 
/*              implementation of virtual functions                             */
/********************************************************************************/ 
const char* exception::exceptionType () const
{
static const char* type = "Laurena's Standard Exception" ;

    return type ;
}


void exception::report(std::ostream& destination) const
{    

    destination << this->exceptionType() 
        << " raised in " << this->_filename 
        << ", at line " << this->_line 
        << " : " << this->_message 
        << std::endl ;
}

/********************************************************************************/ 
/*              print : send report of the exception on the debug interface     */ 
/********************************************************************************/ 
void exception::print () const
{
    debug::println (this->_what) ;
    debug::printStackTrace () ;
}

void exception::ready()
{
    std::ostringstream o;
    this->report(o);
    this->_what = o.str();

}

const char* exception::what() const throw()
{
    return this->_what.c_str();

}
//end of file

