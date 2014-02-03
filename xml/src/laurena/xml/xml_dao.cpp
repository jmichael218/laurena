///
/// \file     xml_dao.cpp
/// \brief    dao for a xml file based persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// dao for a xml file based persistance
///
#include <laurena/xml/xml_dao.hpp>
#include <laurena/xml/xml_oarchive.hpp>
#include <laurena/xml/xml_iarchive.hpp>

using namespace laurena;
using namespace xml;

xml_dao::xml_dao (const descriptor& desc, const std::string& directory) : file_dao(desc, directory)
{ 
    std::cout << this->_directory << std::endl;
}

xml_dao::~xml_dao()
{ }

const std::string& xml_dao::extension ()
{
    static std::string EXTENSION = "xml";
    return EXTENSION;
}
std::shared_ptr<oarchive>  xml_dao::formatter ()
{
    return std::make_shared<oarchive_xml>();

}

std::shared_ptr<iarchive> xml_dao::parser    ()
{
    return std::make_shared<iarchive_xml>();
}
//End of file
