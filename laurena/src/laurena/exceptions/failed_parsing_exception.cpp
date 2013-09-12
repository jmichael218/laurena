///
/// \file     failed_parsing_exception.hpp
/// \brief    Describes a failure in a parsing
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describes a failure in a parsing
///

#include <laurena/exceptions/failed_parsing_exception.hpp>

using namespace laurena;


failed_parsing_exception::failed_parsing_exception (const char* message, const char* source, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line)
{
    _source = source;
    this->ready();
}

failed_parsing_exception::failed_parsing_exception  (const char* message, const std::string& source, const char* filename, const char* function, word32 line) 
     : exception(message, filename, function, line)
{
    _source = source;
    this->ready();

}

failed_parsing_exception::failed_parsing_exception (const char* message, std::istream& source, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line)
{
    char destination [ 1040 ];
    source.read(destination,1024);

    if (source.eof())
        strcat(destination," ...");  

    _source = destination;
    this->ready();

}

const char* failed_parsing_exception::exceptionType () const
{
static const char* type = "Failed Parsing Exception" ;

    return type ;
}

void failed_parsing_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
    destination << "    sourcecode=" << this->_source << std::endl ;
}
