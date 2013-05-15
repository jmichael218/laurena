///
/// \file     formats.hpp
/// \brief    formats is a map of format associated to a field or to a type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// formats is a map of format associated to a field or to a type
///

#ifndef LAURENA_FORMATS_H
#define LAURENA_FORMATS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/formatting/format.hpp>
#include <laurena/descriptors/field.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class archive_format
{
public:    

    /****************************************************************************/ 
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    archive_format ();

    /****************************************************************************/ 
    /*          setters                                                         */ 
    /****************************************************************************/ 
    void format_field(const field& fld, format* fmt);
    void format_type(const descriptor& desc, format* fmt);

    const format* find_field(const field& fld)        const;
    const format* find_type(const descriptor& desc)   const;

    /****************************************************************************/ 
    /*      protected datas                                                     */ 
    /****************************************************************************/ 
    protected:

    std::string    _language;
    format_map     _fields;
    format_map     _types;
};

class archive_format_map : public std::unordered_map<std::string,archive_format>
{    
public:

    const archive_format* get (const std::string& key) const;
};

extern archive_format_map formats;

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
