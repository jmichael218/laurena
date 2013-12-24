///
/// \file     format_epoch.hpp
/// \brief    format_epoch is a measure in seconds of a date or a duration
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_epoch is a measure in seconds of a date or a duration
///

#ifndef LAURENA_FORMAT_EPOCH_H
#define LAURENA_FORMAT_EPOCH_H

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
class writer_epoch : public writer
{
public:    

	writer_epoch			 ();

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool write (std::ostream& output, any& value) const;

};

class parser_epoch : public charset_parser
{
public:    

	parser_epoch ();

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

};

class format_epoch : public format
{
public:

    format_epoch (const char* language);
	format_epoch (const std::string& language);

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
