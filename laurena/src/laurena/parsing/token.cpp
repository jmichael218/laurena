///
/// \file     token.cpp
/// \brief    An extension of any to store token information in parsing process
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An extension of any to store token information in parsing process
///
#include <laurena/parsing/token.hpp>

using namespace laurena;

token::token () : any() , _token_id (0xFFFFFFFF)
{}

token::token (const token &tk) : any((const any&)tk), _token_id(tk._token_id)
{ }

token::token (      token &&tk) : any((any&&)tk), _token_id(tk._token_id)
{ }

token& token::operator=(const token& t)
{
	this->any::operator=((const any&)t);
	this->_token_id = t._token_id;
	return *this;
}

token& token::operator=( token&& t)
{
	this->any::operator=((any &&)t);
	this->_token_id = t._token_id;
	return *this;
}

token& token::operator=(const any& value)
{
	this->any::operator=(value);
	return *this;
}

//End of file
