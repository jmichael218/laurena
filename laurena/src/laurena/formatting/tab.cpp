///
/// \file     tab.cpp
/// \brief    This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
/// \author   Frederic Manisse
/// \version  1.0
///
/// This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
///
#include <laurena/formatting/tab.hpp>

using namespace laurena;

tab::tab (const std::string& sequence, word16 initial_length) : _sequence (sequence) , _tab_length(initial_length)
{
    for (word16 i = 0; i < initial_length; i ++) 
        _tab.append(sequence);
}

tab& tab::decrease() 
{
    if (this->_tab_length)
    {
        -- this->_tab_length;
        this->_tab.erase (this->_tab_length * this->_sequence.length());
    }
    return *this;
}

tab& tab::increase()
{
    ++ this->_tab_length;
    this->_tab.append(this->_sequence);
    return *this;
}
//End of file
