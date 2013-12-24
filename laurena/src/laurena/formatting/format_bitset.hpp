///
/// \file     format_bitset.hpp
/// \brief    format_bitset is a list of keyword for a bitset format
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_bitset is a list of keyword for a bitset format
///

#ifndef LAURENA_FORMAT_BITSET_H
#define LAURENA_FORMAT_BITSET_H

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
class writer_bitset : public writer
{
public:    

	writer_bitset			 (const string_array& values);

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool write (std::ostream& output, any& value) const;

protected:

	const string_array&		_values;
};

class parser_bitset : public charset_parser
{
public:    

	parser_bitset (const string_array& values);

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

protected:

	const string_array&		_values;

};

class format_bitset : public format
{
public:

    format_bitset (const char* language, const string_array& values);
	format_bitset (const std::string& language, const string_array& values);

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
