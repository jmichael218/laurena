///
/// \file     xml_interface.cpp
/// \brief    interface to mask internal calls to serialize from/to xml
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to xml
///
#include <laurena/xml/xml_iarchive.hpp>
#include <laurena/xml/xml_oarchive.hpp>
#include <laurena/xml/xml_interface.hpp>

using namespace laurena;
using namespace xml;

std::string& laurena::xml::xml::serialize(std::string& destination, const std::string& name, const any& value)
{
    oarchive_xml a;

    a.serialize(name,value,false);

    return destination = a.str();
}
//End of file
