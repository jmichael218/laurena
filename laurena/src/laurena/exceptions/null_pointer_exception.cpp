///
/// \file       null_pointer_exception.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      A null pointer exception
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A null pointer exception
///

#include <laurena/exceptions/null_pointer_exception.hpp>

using namespace laurena;

null_pointer_exception::null_pointer_exception (const char* message, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line)
{
    this->ready();
}

null_pointer_exception::null_pointer_exception(const std::string& message, const char* filename, const char* function, word32 line)
                    : exception(message.c_str(), filename, function, line)
{
    this->ready();
}

const char* null_pointer_exception::exceptionType () const
{
static const char* type = "Null Pointer Exception" ;

    return type ;
}

void null_pointer_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
}
//End of file

