///
/// \file     parameter.hpp
/// \brief    A type to describe the parameter of a function/command
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A type to store a named variable of Any type
///
#include <laurena/algorithm/strings/readuntil.hpp>
#include <laurena/algorithm/strings/skipwhile.hpp>


#include <laurena/functions/parameter.hpp>
#include <laurena/constants/const_charsets.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>
#include <laurena/descriptors/classes.hpp>
#include <laurena/descriptors/string_descriptor.hpp>

using namespace laurena;

const string_array parameter::FlagsKeywords = "mandatory line" ;

/********************************************************************************/ 
/*          code for class Parameter                                            */ 
/********************************************************************************/ 
parameter::parameter ()
{
    this->_descriptor = NULL;
    this->_flags.resize(parameter::MAX_FLAGS);
}

const char* parameter::parse(any& value, const char* input) const
{
	// skip spaces
    input = skipwhile(input,const_charsets<>::TABS_NO_EOL.condition());

	if (!*input || const_charsets<>::RN.test(*input))
    {
        if ( this->_flags.test(parameter::FLAG_MANDATORY))                
            return nullptr;
    }

    std::string svalue;
    if (this->_flags.test(parameter::FLAG_LINE))
        svalue = std::move(readuntil(input,const_charsets<>::RN.condition()));
    else
        svalue = std::move(readuntil(input,const_charsets<>::TABS.condition()));
    
    this->_descriptor->stoa(svalue, value);
    return input + svalue.length();
}
/********************************************************************************/ 
/*          code for class ParameterArray                                       */ 
/********************************************************************************/ 
parameters::parameters () : std::vector<parameter>()
{
}

bool parameters::parse (context& c, const std::string& input) const
{
bool ret = true;
const char* s = input.c_str();

    for (const parameter& p : *this)
    {  
        s = p.parse(c[p._name]._value,s);
		if (!s)
			return false;
    }
    return ret;
}

// syntax is [flags]<type> <name>. '*' is for non mandatory. keyword is string without flag LINE
bool parameters::syntax (const std::string& src)
{

	const char* s = src.c_str();
	std::list<parameter> tmplist;

	std::string classtype;

	while (*s)
	{
		parameter p;

		// read classtype and flags
		if (*s == '*')
			++s;
		else
			p._flags.set(parameter::FLAG_MANDATORY);		

		classtype = readuntil(s, const_charsets<>::TABS.condition());

		// set type
		if (classtype == "keyword")
			p._descriptor = td<std::string>::desc();
		else if (classtype == "string")
		{
			p._descriptor = td<std::string>::desc();
			p._flags.set(parameter::FLAG_LINE);
		}
		else
			p._descriptor = classes::byName(classtype);

		if (!p._descriptor)
			return false;

		// skip classtype
		s += classtype.length();
		s = skipwhile(s, const_charsets<>::TABS.condition());

		// read parameter name
		p._name = readuntil(s, const_charsets<>::TABS.condition());
		s += p._name.length();
		s = skipwhile(s, const_charsets<>::TABS.condition());

		tmplist.push_back(p);
	}

	this->assign(tmplist.begin(), tmplist.end());
	return true;
}
/********************************************************************************/ 
//End of file

