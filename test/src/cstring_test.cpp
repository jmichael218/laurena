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
    testunit::startTest("basic test : cstring::readWhile ('0123EREZC' , 'CHARSET_NUMBER')");
    word32 w4 = cstring::readWhile("0123EREZC",s4,const_charsets<>::NUMBERS);
    std::string rs4 = readwhile("0123EREZC",const_charsets<>::NUMBERS.condition());
    testunit::endTest(w4 == 4 && s4 == "0123" && rs4 == "0123" );
    
    // failed test
    std::string s5;
    testunit::startTest("basic failed test : cstring::readWhile ('Z0123EREZC' , 'CHARSET_NUMBER')");
    word32 w5 = cstring::readWhile("Z0123EREZC",s5,const_charsets<>::NUMBERS);
    std::string rs5 = readwhile("Z0123EREZC",const_charsets<>::NUMBERS.condition());
    testunit::endTest(w5 == 0 && s5 == "" && rs5 == "" );    
    
}


//End of file
