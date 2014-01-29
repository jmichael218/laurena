///
/// \file     json_dao.cpp
/// \brief    dao for a json file based persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// dao for a json file based persistance
///
#include <laurena/json/json_dao.hpp>
#include <laurena/json/oarchive_json.hpp>
#include <laurena/json/iarchive_json.hpp>

using namespace laurena;
using namespace json;

json_dao::json_dao (const descriptor& desc, const std::string& directory) : file_dao(desc, directory)
{ 
    std::cout << this->_directory << std::endl;
}

json_dao::~json_dao()
{ }

const std::string& json_dao::extension ()
{
    static std::string EXTENSION = "json";
    return EXTENSION;
}
std::shared_ptr<oarchive>  json_dao::formatter ()
{
    return std::make_shared<oarchive_json>();

}

std::shared_ptr<iarchive> json_dao::parser    ()
{
    return std::make_shared<iarchive_json>();
}
//End of file
