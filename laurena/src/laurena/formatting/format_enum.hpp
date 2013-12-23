///
/// \file     format_enum.hpp
/// \brief    format_enum is a keyword enum format
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_enum is a keyword enum format
///

#ifndef LAURENA_FORMAT_ENUM_H
#define LAURENA_FORMAT_ENUM_H

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
#include <laurena/types/string_array.hpp>
#include <laurena/parsing/basic_parsers.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class writer_enum : public writer
{
public:    

	writer_enum			 (const string_array& values);

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool write (std::ostream& output, any& value) const;

protected:

	const string_array&		_values;
};

class parser_enum : public charset_parser
{
public:    

	parser_enum (const string_array& values);

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

protected:

	const string_array&		_values;

};

class format_enum : public format
{
public:

    format_enum (const char* language, const string_array& values);

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
