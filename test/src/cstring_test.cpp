///
/// \file     cstring.cpp
/// \brief    Test cstring class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test cstring class
//
#include <laurena/constants/const_charsets.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>
#include <laurena/laurena.hpp>

using namespace laurena;


void cstring_test ()
{
    testunit::type("cstring");

    testunit::function("cstring::readWhile(...)");

    // basic test
    std::string s4;
    testunit::start("basic test : cstring::readWhile ('0123EREZC' , 'CHARSET_NUMBER')");
	s4 = readwhile("0123EREZC",const_charsets<>::NUMBERS.condition());
    word32 w4 = s4.length();
	const char* cc4 = "0123EREZC";
    std::string rs4 = readwhile(cc4,const_charsets<>::NUMBERS.condition());
    testunit::end(w4 == 4 && s4 == "0123" && rs4 == "0123" );
    
    // failed test
    std::string s5;
    testunit::start("basic failed test : cstring::readWhile ('Z0123EREZC' , 'CHARSET_NUMBER')");
	s5 = readwhile ("Z0123EREZC",const_charsets<>::NUMBERS.condition());
    word32 w5 = s5.length();
	const char* cc5 = "Z0123EREZC";
    std::string rs5 = readwhile("Z0123EREZC",const_charsets<>::NUMBERS.condition());
    testunit::end(w5 == 0 && s5 == "" && rs5 == "" );  

	typedef in_traits<const char [5]> ii;

	ii::chartype c = 'r' ;

	return;
    
}


//End of file
