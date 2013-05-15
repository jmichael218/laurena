///
/// \file     formats.cpp
/// \brief    formats is a map of format associated to a field or to a type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// formats is a map of format associated to a field or to a type
///
#include <laurena/formatting/formats.hpp>

using namespace laurena;

archive_format_map laurena::formats;

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class archive_format                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

archive_format::archive_format () : _fields (), _types () {}

void archive_format::format_field(const field& fld, format* fmt)
{
    std::string key = fld.desc().name ();
    key.append("->").append(fld.name());
    this->_fields [key] = fmt;
}

void archive_format::format_type(const descriptor& desc, format* fmt)
{
    this->_types [desc.name()] = fmt;
}

const format* archive_format::find_field(const field& fld)        const
{
    std::string key = fld.desc().name ();
    key.append("->").append(fld.name());
    return this->_fields.get(key);
}

const format* archive_format::find_type(const descriptor& desc)   const
{
    return this->_types.get(desc.name());
}

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class archive_format                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

const archive_format* archive_format_map::get (const std::string& key) const
{
    auto it = this->find(key);
    return it == this->end() ? nullptr : &it->second;
}
//End of file
