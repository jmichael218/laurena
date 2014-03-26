///
/// \file     string_array_descriptor_test.cpp
/// \brief    Test String array serialization
/// \author   Frederic Manisse
/// \version  1.0
///
/// Test String array serialization
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testStringArrayGetFieldValue()
{
    string_array sa ;
    sa.push_back("one");
    sa.push_back("two");
    sa.push_back("three");

	string_array sa3;
	sa3.attributes(&sa);
	sa3 [0] = "un";
	sa3 [1] = "deux";
	sa3 [2] = "trois";

    const descriptor* cd = td<string_array>::desc();

	any a;
	cd->getFieldValue(&sa3, "one", a);
	assert(anycast<std::string>(a) == "un");


}

void testStringArrayDescriptor()
{
    testunit::type("descriptor<string_array>");
    
    // is the descriptor existing ?
    testunit::start("is descriptor<string_array> defined ?");
    const descriptor* cd = td<string_array>::desc();
    testunit::end(cd != nullptr);

    testunit::start("serialize a string array");
    string_array sa ;
    sa.push_back("one");
    sa.push_back("two");
    sa.push_back("three");

    std::string serialized;
    oarchive_mdl::tostring(serialized, "stringArray", &sa);
    testunit::log() << serialized << std::endl;  
	testunit::end(true);

    testunit::start("test string array's key mapper");
	string_array sa3;
	sa3.attributes(&sa);
	sa3 [0] = "un";
	sa3 [1] = "deux";
	sa3 [2] = "trois";

	serialized = laurena::mdl::mdl::serialize(sa3);
    testunit::log() << serialized << std::endl;    

	string_array sa4;
	sa4.attributes(&sa);
	laurena::mdl::mdl::parse(serialized, sa4);

	testunit::end(sa4[0] == "un");

	testStringArrayGetFieldValue();

}

