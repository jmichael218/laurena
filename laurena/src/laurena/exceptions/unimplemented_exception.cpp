///
/// \file       unimplemented_exception.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Calling a function unimplemented for this class exception
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Calling a function unimplemented for this class exception
///

#include <laurena/exceptions/unimplemented_exception.hpp>

using namespace laurena;

unimplemented_exception::unimplemented_exception (const char* message, const char* filename, word32 line)
                    : exception(message, filename, line)
{
    this->ready();
}

const char* unimplemented_exception::exceptionType () const
{
static const char* type = "Unimplemented code Exception" ;

    return type ;
}

void unimplemented_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
}
//End of file

