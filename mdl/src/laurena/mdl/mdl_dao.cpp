///
/// \file     mdl_dao.cpp
/// \brief    dao for a mdl file based persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// dao for a mdl file based persistance
///
#include <laurena/mdl/mdl_dao.hpp>
#include <laurena/mdl/oarchive_mdl.hpp>
#include <laurena/mdl/iarchive_mdl.hpp>

using namespace laurena;
using namespace mdl;

mdl_dao::mdl_dao (const descriptor& desc, const std::string& directory) : file_dao(desc, directory)
{ 
    std::cout << this->_directory << std::endl;
}

mdl_dao::~mdl_dao()
{ }

const std::string& mdl_dao::extension ()
{
    static std::string EXTENSION = "mdl";
    return EXTENSION;
}
std::shared_ptr<oarchive>  mdl_dao::formatter ()
{
    return std::make_shared<oarchive_mdl>();

}

std::shared_ptr<iarchive> mdl_dao::parser    ()
{
    return std::make_shared<iarchive_mdl>();
}
//End of file
