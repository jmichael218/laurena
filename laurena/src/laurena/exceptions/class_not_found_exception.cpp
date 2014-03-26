///
/// \file       class_not_found_exception.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      An exception occuring when a class descriptor is null
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An exception occuring when a class descriptor is null
///

#include <laurena/exceptions/class_not_found_exception.hpp>

using namespace laurena;

class_not_found_exception::class_not_found_exception (const type_info& type, const char* message, const char* filename, const char* function, word32 line)
                    : exception(message, filename, function, line), _type(type)
{
    this->ready();
}

class_not_found_exception::class_not_found_exception(const type_info& type, const std::string& message, const char* filename, const char* function, word32 line)
                    : exception(message.c_str(), filename, function, line), _type(type)
{
    this->ready();
}

const char* class_not_found_exception::type () const
{
static const char* type = "Class Not Found Exception" ;

    return type ;
}

void class_not_found_exception::report(std::ostream& destination) const
{
    this->exception::report(destination) ;
    destination << "    class not found: {type=" << this->_type.name() << ", hash=" << std::type_index(this->_type).hash_code() << std::endl;
}
//End of file

