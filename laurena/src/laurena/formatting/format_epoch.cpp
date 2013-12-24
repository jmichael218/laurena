///
/// \file     format_epoch.cpp
/// \brief    format_epoch is a measure in seconds of a date or a duration
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_epoch is a measure in seconds of a date or a duration
///
#include <laurena/formatting/format_epoch.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

writer_epoch::writer_epoch() : writer ()
{ }

// Format is d/m/Y H:M:S
bool writer_epoch::write (std::ostream& output, any& value) const
{
	word64 w = anycast<word64>(value);
	std::time_t t = (std::time_t) w;
	char mbstr[100];
	std::strftime(mbstr, 100, "%d/%m/%Y %H:%M:%S", std::localtime(&t));
	output << mbstr;
	return true;
}

parser_epoch::parser_epoch () : charset_parser(const_charsets<>::VARNAME)
{ }

//! a tokenizer is providing a list of tokens from a source code.
bool parser_epoch::read (tokenizer& tokenizer, any& value, bool consume) const
{

	return true;
}
//End of file
