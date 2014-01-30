///
/// \file     file_dao.cpp
/// \brief    DAO base class for file based DAO
/// \author   Frederic Manisse
/// \version  1.0
///
/// DAO base class and templated class
///
#include <laurena/persistance/file_dao.hpp>
#include <laurena/toolboxes/loader.hpp>
#include <laurena/descriptors/field.hpp>

#include <boost/filesystem.hpp>

using namespace laurena;

file_dao::file_dao (const descriptor& desc, const std::string& directory) : dao(desc), _directory(directory)
{  }

file_dao::~file_dao()
{ }

std::string file_dao::directory(const std::string& key)
{
    char letter [2] = "a";
    letter[0] = UPPER(*key.c_str());

    std::ostringstream sfilename;

    sfilename << this->_directory << "/" 
              << letter
              ;

    return sfilename.str();
}

std::string file_dao::filename(const std::string& key)
{
    std::ostringstream sfilename;

    sfilename << key << "." << this->extension()
              ;

    return sfilename.str();
}

std::string file_dao::path(const std::string& key)
{
    std::string res = this->directory(key);
    return res.append("/").append(this->filename(key));
}

any& file_dao::read    (const any& primaryKey, any& destination)
{
    std::string skey = primaryKey.tos();

    std::string content = loader<>::load(this->path(skey));

    std::shared_ptr<iarchive> arc = this->parser();
    arc->reader().str(content.c_str());

    arc->parse(this->_descriptor.name(), destination);

    return destination;

}



any& file_dao::create  (any& object)
{
    return this->update(object);
}

any& file_dao::update  (any& object)
{
    // recuperation primary key
    any primaryKey;
    this->_descriptor.primaryKey().get(object, primaryKey);
    std::string skey = primaryKey.tos();

    std::shared_ptr<oarchive> arc = this->formatter();
    arc->serialize(this->_descriptor.name(), object);

    // create directories if needed
    boost::filesystem::path p (this->directory(skey));
    boost::filesystem::create_directories(p);

    std::ofstream out(this->path(skey));
    out << arc->str();
    out.close();

    return object;
}

void file_dao::erase   (any& object)
{
    any primaryKey;
    this->_descriptor.primaryKey().get(object, primaryKey);
    this->erase(primaryKey);
}

void file_dao::erase   (const any& primaryKey)
{
    std::string skey = primaryKey.tos();

    boost::filesystem::path p (this->path(skey));
    boost::filesystem::remove(p);
}

bool file_dao::exist   (const any& primaryKey)
{
    std::string skey = primaryKey.tos();

    boost::filesystem::path p (this->path(skey));
    return boost::filesystem::exists(p);
}
//End of file


