///
/// \file     file_serial_manager.cpp
/// \brief    A file based manager for a table of serial ID
/// \author   Frederic Manisse
/// \version  1.0
///
/// A file based manager for a table of serial ID
///
#include <laurena/persistance/file_serial_manager.hpp>
#include <laurena/descriptors/field.hpp>

#include <laurena/archives/oarchive.hpp>
#include <laurena/archives/iarchive.hpp>

#include <boost/filesystem.hpp>

using namespace laurena;

file_serial_manager::file_serial_manager(persistance& engine, const std::string& spipeline, language& fileformat, const std::string& directory) 
    
    : serial_manager(engine, spipeline), _language(fileformat), _directory(directory)
{ }

file_serial_manager::file_serial_manager(persistance& engine, const char* spipeline, language& fileformat, const char* directory) 
    : serial_manager(engine, spipeline), _language(fileformat), _directory(directory)
{ }


file_serial_manager::~file_serial_manager()
{ }

std::string file_serial_manager::filename(const any& serialKey)
{
    std::string filename = this->_directory;
    filename.append("/").append(serialKey.tos()).append(this->_language.name());
    return filename;
}
void file_serial_manager::create(any object)                             
{
    any serialkey;
    object.desc()->serial().get(object, serialkey);

    std::string sfilename = std::move(this->filename(serialkey));

    oarchive::sptr w = this->_language.writer();
    w->serialize("serial", object);

    // create directories if needed
    boost::filesystem::path p (this->_directory);
    boost::filesystem::create_directories(p);

    std::ofstream out(sfilename);
    out << w->str();
    out.close();

}

void file_serial_manager::read  (const any& serialKey, any destination) 
{
}

bool file_serial_manager::exist (const any& serialKey)
{
    std::string sfilename = std::move(this->filename(serialKey));

    boost::filesystem::path p (sfilename);
    return boost::filesystem::exists(p);
}

bool file_serial_manager::remove(const any& serialKey)
{
    return false;
}

//End of file