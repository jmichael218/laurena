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

bool parameter::parse(any& value, std::istream& input) const
{
    skipwhile(input,const_charsets<>::TABS_NO_EOL.condition());
    if ( input.eof() || const_charsets<>::RN.test(input.peek()))
    {
        if ( this->_flags.test(parameter::FLAG_MANDATORY))                
            return false;
    }

    std::string svalue;
    if (this->_flags.test(parameter::FLAG_LINE))
        svalue = std::move(readuntil(input,const_charsets<>::RN.condition()));
    else
        svalue = std::move(readuntil(input,const_charsets<>::TABS.condition()));
    
    this->_descriptor->stoa(svalue, value);
    return true;
}
/********************************************************************************/ 
/*          code for class ParameterArray                                       */ 
/********************************************************************************/ 
parameters::parameters () : std::vector<parameter>()
{
}

bool parameters::parse (context& c, std::istream& input) const
{
bool ret = true;

    for (word32 i = 0 ; i < this->size(); i ++)
    {
        const parameter& p = this->operator[](i);       
        ret &= p.parse(c[p.name()]._value,input);
    }
    return ret;
}
/********************************************************************************/ 
//End of file


