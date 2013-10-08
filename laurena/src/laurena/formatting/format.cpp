///
/// \file     format.cpp
/// \brief    format is a parser + a writer pair
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format is a parser + a writer pair
///

#include <laurena/formatting/format.hpp>
#include <laurena/descriptors/field.hpp>

using namespace laurena;

format::format (const char* language, writer* w, parser* f) : annotation(language), _writer(w) , _parser(f) {}

bool format::write (std::ostream& output, any& value) const
{
    return this->_writer->write(output,value);
}

bool format::read (tokenizer& tokenizer, any& value, bool consume) const
{
    return this->_parser->read (tokenizer,value,consume);
}

bool format::acceptDescriptable ()
{
	return nullptr != dynamic_cast<descriptor*>(this->_descriptable) || nullptr != dynamic_cast<field*>(this->_descriptable);
}
//End of file
