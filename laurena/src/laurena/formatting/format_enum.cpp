///
/// \file     format_enum.cpp
/// \brief    format_enum is a keyword enum format
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_enum is a keyword enum format
///
#include <laurena/formatting/format_enum.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

writer_enum::writer_enum(const string_array& values) : writer (), _values(values)
{ }

bool writer_enum::write (std::ostream& output, any& value) const
{
	output << this->_values [ anycast<int>(value)] ; 
	return true;
}

parser_enum::parser_enum (const string_array& values) : charset_parser(const_charsets<>::VARNAME), _values(values)
{ }

//! a tokenizer is providing a list of tokens from a source code.
bool parser_enum::read (tokenizer& tokenizer, any& value, bool consume) const
{
	any str;
	bool res = this->charset_parser::read(tokenizer, str, consume);
	if (!res)
		return res;

	int32 index = this->_values.findExact(anycast<std::string>(str));
	if (index == -1)
		return false;

	value = index;
	return true;
}

format_enum::format_enum (const char* language, const string_array& values) : format(language)
{ 
	this->_writer = std::make_shared<writer_enum>(values);
	this->_parser =  std::make_shared<parser_enum>(values);

}
//End of file
