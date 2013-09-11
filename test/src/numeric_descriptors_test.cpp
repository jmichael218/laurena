///
/// \file     numeric_descriptors_test.cpp
/// \brief    Test numeric type descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test numeric type descriptors
//
#include <laurena/laurena.hpp>

using namespace laurena;

void testWord8Descriptor ()
{
any a;
std::string s;
word8 w ;

    testunit::type("descriptor<word8>");

    // is the descriptor existing ?
    testunit::startTest("is descriptor<word8> defined ?");
    const descriptor* tdword8 = td<word8>::desc();
    testunit::endTest(tdword8 != nullptr);

    testunit::function("descriptor<word8>::has");
    testunit::startTest("descriptor<word8> is a numeric value ?");
    testunit::endTest(tdword8 ? tdword8->has(descriptor::Flags::NUMERIC_VALUE) : false) ;

    testunit::function("descriptor<word8>::toString");
    testunit::startTest("casting word8(12) to std::string");
    a = (word8) 12;
    s = tdword8->atos(a);
    testunit::endTest(s == "12");           

    testunit::function("descriptor<word8> fromString");
    testunit::startTest("casting \"14\" to word8");
    s = "14";
    tdword8->stoa(s, a);
    w = anycast<word8>(a);
    testunit::endTest(w == 14);
}

void testInt8Descriptor()
{
any a;
std::string s;
int8 w ;

    testunit::type("descriptor<int8>");

    // is the descriptor existing ?
    testunit::startTest("is descriptor<int8> registered under 'int8' name ?");
    const descriptor* tdint8 = classes::byName("int8");
    testunit::endTest(tdint8 != nullptr);

    testunit::startTest("is descriptor<int8> match 'char' type descriptor ?");
    tdint8 = classes::byType(typeid(int8));
    testunit::endTest(tdint8 != nullptr);    

    testunit::function("descriptor<int8>::has");
    testunit::startTest("descriptor<int8> is a numeric value ?");
    testunit::endTest(tdint8 ? tdint8->has(descriptor::Flags::NUMERIC_VALUE) : false) ;

    testunit::function("descriptor<int8>::toString");
    testunit::startTest("casting int8(12) to std::string");
    a = (int8) 12;
    s = tdint8->atos(a);
    testunit::endTest(s == "12");          

    testunit::startTest("casting int8(-42) to std::string");
     a = (int8) -42;
    s = tdint8->atos(a);
    testunit::endTest(s == "-42");     

    testunit::function("descriptor<int8> fromString");
    testunit::startTest("casting \"14\" to int8");
    s = "14";
    tdint8->stoa(s, a);
    w = anycast<int8>(a);
    testunit::endTest(w == 14);

    testunit::startTest("casting \"-34\" to int8");
    s = "-34";
    tdint8->stoa(s, a);
    w = anycast<int8>(a);
    testunit::endTest(w == -34);
}

void testNumericDescriptors ()
{
    testWord8Descriptor();
    testInt8Descriptor();

}
//End of file


