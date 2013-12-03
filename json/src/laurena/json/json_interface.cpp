///
/// \file     json_interface.cpp
/// \brief    interface to mask internal calls to serialize from/to json
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to json
///
#include <laurena/json/iarchive_json.hpp>
#include <laurena/json/oarchive_json.hpp>
#include <laurena/json/json_interface.hpp>

using namespace laurena;
using namespace json;

std::string& laurena::json::json::serialize(std::string& destination, const std::string& name, const any& value, word32 flags)
{
    oarchive_json ajson;
    ajson.compact( flags & json::COMPACT );
	ajson.nowrapper((flags & json::NO_WRAPPER) == json::NO_WRAPPER);

    ajson.serialize(name,value,false);

    return destination = ajson.str();
}
//End of file
