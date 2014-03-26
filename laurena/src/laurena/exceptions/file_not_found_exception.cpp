///
/// \file     file_not_found_exception.cpp
/// \brief    A file not found exception
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A file not found exception
///

#include <laurena/exceptions/file_not_found_exception.hpp>

using namespace laurena;


file_not_found_exception::file_not_found_exception (const char* message, const std::string& fileNotFound, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line), _file_not_found(fileNotFound)
{
    this->ready();
}


const char* file_not_found_exception::type () const
{
static const char* type = "File Not Found Exception" ;

    return type ;
}

void file_not_found_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
    destination << "    file not found=" << this->_file_not_found;
}
//End of file
