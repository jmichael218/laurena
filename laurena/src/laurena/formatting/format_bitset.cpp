///
/// \file     format_bitset.cpp
/// \brief    format_bitset is a list of keyword for a bitset format
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format_bitset is a list of keyword for a bitset format
///

#include <laurena/formatting/format_bitset.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/constants/const_charsets.hpp>
#include <laurena/constants/const_strings.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/exceptions/unimplemented_exception.hpp>
#include <laurena/toolboxes/bitset.hpp>

using namespace laurena;

writer_bitset::writer_bitset(const string_array& values) : writer (), _values(values)
{ }

bool writer_bitset::write (std::ostream& output, any& value) const
{
const descriptor* d = value.desc();
std::string destination;

	if (!d)
		throw LAURENA_NULL_POINTER_EXCEPTION("No descriptor.");

	if (d->has(descriptor::Flags::NUMERIC_VALUE))
    {
        word64 wbits = anycast<word64>(value);
        bitset::serialize(wbits,this->_values,destination,CONST_SPACE);            
    } 
    else                
    {
		boost::dynamic_bitset<>* bset = anycast<boost::dynamic_bitset<>*>(value);        
        bitset::serialize(*bset,this->_values,destination,CONST_SPACE);
    }

	output << destination ; 
	return true;
}

parser_bitset::parser_bitset (const string_array& values) : charset_parser(const_charsets<>::VARLIST), _values(values)
{ }

//! a tokenizer is providing a list of tokens from a source code.
bool parser_bitset::read (tokenizer& tokenizer, any& value, bool consume) const
{

	any a;
	bool res = this->charset_parser::read(tokenizer, a, consume);
	if (!res)
		return res;

	std::string str = std::move(anycast<std::string>(a));

const descriptor* d = value.desc();

	if (d && d->name() == "bitset")
	{
		boost::dynamic_bitset<>* p = anycast<boost::dynamic_bitset<>*>(value); 
		if (p->size() != this->_values.size())
				p->resize(this->_values.size());
        bitset::parse(*p,this->_values,const_charsets<>::VARNAME,str);
	}
	else
    if (!d || d->has(descriptor::Flags::NUMERIC_VALUE))
    {
            word64 b = bitset::parse(this->_values,const_charsets<>::VARNAME,str);
            value = b;
    } 
	else
		throw LAURENA_NULL_POINTER_EXCEPTION("class parser_bitset currently support only numerical type and boost::dynamic_bitset<>.");
}

format_bitset::format_bitset (const char* language, const string_array& values) : format(language)
{ 
	this->_writer = std::make_shared<writer_bitset>(values);
	this->_parser =  std::make_shared<parser_bitset>(values);

}

format_bitset::format_bitset (const std::string& language, const string_array& values) : format(language.c_str())
{ 
	this->_writer = std::make_shared<writer_bitset>(values);
	this->_parser =  std::make_shared<parser_bitset>(values);

}
//End of file
