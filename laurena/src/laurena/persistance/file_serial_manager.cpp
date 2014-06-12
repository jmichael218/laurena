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
#include <laurena/toolboxes/loader.hpp>

#include <laurena/archives/oarchive.hpp>
#include <laurena/archives/iarchive.hpp>

#include <laurena/casting/lexical_cast.hpp>

#include <boost/filesystem.hpp>

using namespace laurena;

file_serial_manager::file_serial_manager(const std::string& spipeline, language& fileformat, const std::string& directory) 
    
    : serial_manager(spipeline), _language(fileformat), _directory(directory)
{ }

file_serial_manager::file_serial_manager(const char* spipeline, language& fileformat, const char* directory) 
    : serial_manager(spipeline), _language(fileformat), _directory(directory)
{ }


file_serial_manager::~file_serial_manager()
{ }

std::string file_serial_manager::filename(const std::string& serialKey) const
{
    std::string filename = this->_directory;
    filename.append("/").append(serialKey).append(".").append(this->_language.name());
    return filename;
}

void file_serial_manager::load_last_serial()
{
    std::string filename = this->_directory;
    filename.append("/index.txt");

    boost::filesystem::path p (filename);
    if (!boost::filesystem::exists(p))
    {
        this->_last_serial = 0;
        return;
    }

    std::string s = std::move(loader<>::load(filename));
    this->_last_serial = lexical_cast<word64>(s);
}

void file_serial_manager::save_last_serial()
{
    boost::filesystem::path p (this->_directory);
    boost::filesystem::create_directories(p);

    std::string filename = this->_directory;
    filename.append("/index.txt");
    std::ofstream out(filename);
    out << this->_last_serial;
    out.close();
}

void file_serial_manager::write(const serial_entry& entry)                              
{
    std::string sfilename = std::move(this->filename(entry._serial));
    oarchive::sptr w = this->_language.writer();
    w->serialize("serial", &entry);

    // create directories if needed
    boost::filesystem::path p (this->_directory);
    boost::filesystem::create_directories(p);

    std::ofstream out(sfilename);
    out << w->str();
    out.close();

}

void file_serial_manager::read  (serial_entry& destination, const std::string& serialKey) 
{
    std::string content = loader<>::load(this->filename(serialKey));

    iarchive::sptr reader = this->_language.reader();
    any res = &destination;
    reader->reader().str(content.c_str());
    reader->parse("serial", res);
}

bool file_serial_manager::exist (const std::string& serialKey)
{
    std::string sfilename = std::move(this->filename(serialKey));

    boost::filesystem::path p (serialKey);
    return boost::filesystem::exists(p);
}

bool file_serial_manager::remove(const std::string& serialKey)
{
    std::string sfilename = std::move(this->filename(serialKey));

    boost::filesystem::path p (sfilename);
    return boost::filesystem::remove(p);

}

//End of file