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
    testunit::start("is descriptor<word8> defined ?");
    const descriptor* tdword8 = td<word8>::desc();
    testunit::end(tdword8 != nullptr);

    testunit::function("descriptor<word8>::has");
    testunit::start("descriptor<word8> is a numeric value ?");
    testunit::end(tdword8 ? tdword8->has(descriptor::Flags::NUMERIC_VALUE) : false) ;

    testunit::function("descriptor<word8>::toString");
    testunit::start("casting word8(12) to std::string");
    a = (word8) 12;
    s = tdword8->atos(a);
    testunit::end(s == "12");           

    testunit::function("descriptor<word8> fromString");
    testunit::start("casting \"14\" to word8");
    s = "14";
    tdword8->stoa(s, a);
    w = anycast<word8>(a);
    testunit::end(w == 14);
}

void testInt8Descriptor()
{
any a;
std::string s;
int8 w ;

    testunit::type("descriptor<int8>");

    // is the descriptor existing ?
    testunit::start("is descriptor<int8> registered under 'int8' name ?");
    const descriptor* tdint8 = classes::by_name("int8");
    testunit::end(tdint8 != nullptr);

    testunit::start("is descriptor<int8> match 'char' type descriptor ?");
    tdint8 = classes::by_type(typeid(int8));
    testunit::end(tdint8 != nullptr);    

    testunit::function("descriptor<int8>::has");
    testunit::start("descriptor<int8> is a numeric value ?");
    testunit::end(tdint8 ? tdint8->has(descriptor::Flags::NUMERIC_VALUE) : false) ;

    testunit::function("descriptor<int8>::toString");
    testunit::start("casting int8(12) to std::string");
    a = (int8) 12;
    s = tdint8->atos(a);
    testunit::end(s == "12");          

    testunit::start("casting int8(-42) to std::string");
     a = (int8) -42;
    s = tdint8->atos(a);
    testunit::end(s == "-42");     

    testunit::function("descriptor<int8> fromString");
    testunit::start("casting \"14\" to int8");
    s = "14";
    tdint8->stoa(s, a);
    w = anycast<int8>(a);
    testunit::end(w == 14);

    testunit::start("casting \"-34\" to int8");
    s = "-34";
    tdint8->stoa(s, a);
    w = anycast<int8>(a);
    testunit::end(w == -34);
}

void testNumericDescriptors ()
{
    testWord8Descriptor();
    testInt8Descriptor();

}
//End of file


