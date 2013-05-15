///
/// \file     cstring.cpp
/// \brief    Test cstring class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test cstring class
//
#include <laurena/laurena.hpp>

using namespace laurena;


void cstring_test ()
{
    testunit::type("cstring");

    testunit::function("cstring::startWith(...)");

    // basic case sensitive test
    testunit::startTest("basic case sensitive test : cstring::startWith('Hello kitty','Hello') == true");
    bool b0 = cstring::startWith("Hello kitty","Hello");
    testunit::endTest(b0);
    
    // basic non case sensitive test
    testunit::startTest("basic non case sensitive test : cstring::startWith('Hello kitty','hello', false) == false");
    bool b1 = cstring::startWith("Hello kitty","hello",false);
    testunit::endTest(b1);

    // basic failed test
    testunit::startTest("basic failed test : cstring::startWith('Hello kitty','Hello kimmie') == false");
    bool b2 = cstring::startWith("Hello kitty","Hello kimmie");
    testunit::endTest(!b2);

    // basic case sensitive test with size
    testunit::startTest("non case sensitive + size test : cstring::startWith('Hello kitty', 'Hello Kimmie',false, 5) == true");
    bool b3 = cstring::startWith("Hello kitty","hElLo Kimmie",false,5);
    testunit::endTest(b3);

    testunit::function("cstring::readWhile(...)");

    // basic test
    std::string s4;
    testunit::startTest("basic test : cstring::readWhile ('0123EREZC' , 'CHARSET_NUMBER')");
    word32 w4 = cstring::readWhile("0123EREZC",s4,CHARSET_NUMBER);
    std::string rs4 = cstring::readWhile("0123EREZC",CHARSET_NUMBER);
    testunit::endTest(w4 == 4 && s4 == "0123" && rs4 == "0123" );
    
    // failed test
    std::string s5;
    testunit::startTest("basic failed test : cstring::readWhile ('Z0123EREZC' , 'CHARSET_NUMBER')");
    word32 w5 = cstring::readWhile("Z0123EREZC",s5,CHARSET_NUMBER);
    std::string rs5 = cstring::readWhile("Z0123EREZC",CHARSET_NUMBER);
    testunit::endTest(w5 == 0 && s5 == "" && rs5 == "" );    
    
}


//End of file
