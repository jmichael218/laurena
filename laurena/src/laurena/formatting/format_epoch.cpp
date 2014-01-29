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


using namespace laurena;

writer_epoch::writer_epoch (const std::string& format, std::shared_ptr<datetime_format> pformatter) : writer (), _format(format), _formatter(pformatter)
{ }

// Format is d/m/Y H:M:S
bool writer_epoch::write (std::ostream& output, any& value) const
{
	word64 epoch = anycast<word64>(value);
	output << _formatter->format(epoch, _format);
	return true;
}

parser_epoch::parser_epoch (const std::string& format, std::shared_ptr<datetime_format> pformatter) : parser(), _format(format), _formatter(pformatter)
{ }

//! a tokenizer is providing a list of tokens from a source code.
bool parser_epoch::read (tokenizer& tokenizer, any& value, bool consume) const
{

    word32 len;
    word64 epoch = _formatter->epoch(tokenizer._ptr, _format, &len);
    if (consume)
    tokenizer._ptr += len;
    value = epoch;
	return true;
}

 format_epoch::format_epoch  (const std::string& language, const std::string& date_format, std::shared_ptr<datetime_format> pformatter): format(language.c_str())
{ 
	this->_writer = std::make_shared<writer_epoch>(date_format, pformatter);
	this->_parser =  std::make_shared<parser_epoch>(date_format, pformatter);

}
//End of file
