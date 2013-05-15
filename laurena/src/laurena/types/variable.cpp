///
/// \file     variable.cpp
/// \brief    A type to store a named variable of any type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A type to store a named variable of Any type
///

#include <laurena/types/variable.hpp>
#include <laurena/debug/debug.hpp>

using namespace laurena;

/********************************************************************************/ 
/*      code for class variable                                                 */ 
/********************************************************************************/

variable::variable () : _name () , _value () {}

variable::variable (const variable& source) : _name (source._name) , _value(source._value) {}

variable::variable (const std::string& name, const any& value) : _name(name) , _value(value) {}

 variable::~variable ()
{ }

/********************************************************************************/ 
/*      code for class variable_list                                            */ 
/********************************************************************************/

variable_list::variable_list () : std::list<variable> ()
{ }

variable_list::~variable_list () 
{ 
    debug::println("~vl");    
}

variable*   variable_list::find(const std::string& name)
{
    for(variable& v : *this)
        if (boost::equals(name,v._name))
            return &v;

    return nullptr;

}

 variable_list& variable_list::add (const std::string& name, const any& value)
{
    this->push_back(variable(name,value));
    return *this;
}
//end of file
