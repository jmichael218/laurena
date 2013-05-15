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

//End of file
