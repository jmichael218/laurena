///
/// \file     bad_cast_exception.cpp
/// \brief    A failed casting exception
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A failed casting exception
///

#include <laurena/exceptions/bad_cast_exception.hpp>

using namespace laurena;


bad_cast_exception::bad_cast_exception (const char* message, const char* castTypename, const char* valueTypename, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line)
{
    this->_cast_typename = castTypename;
    this->_value_typename = valueTypename;
    this->ready();
}

const char* bad_cast_exception::exceptionType () const
{
static const char* type = "Bad Cast Exception" ;

    return type ;
}

void bad_cast_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
    destination << "    casting type=" << this->_cast_typename << std::endl 
                << "    value type  =" << this->_value_typename << std::endl;
}
