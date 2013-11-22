///
/// \file     mdl_serialization_test.cpp
/// \brief    test functions for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// test functions for the mdl language
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testBasicMdlSerialization ()
{
    character bob;
    bob._name = "Bob" ;
    bob._age = 28;

    testunit::type("MDL - simple object");
    testunit::function("oarchive_mdl::toString + iarchive_mdl::fromString - simple object");

    std::string serialized_bob;
    oarchive_mdl::tostring(serialized_bob, "character", &bob);

    testunit::log() << serialized_bob << std::endl;

    character bob2;
    any a2 = &bob2;
    iarchive_mdl::fromString(serialized_bob.c_str(),"character",a2);
    
    testunit::endTest(bob2._name == "Bob" && bob2._age == 28 );

    return;
}

void testMdlArray()
{
	string_array sa = "one two three";
	std::string serialized_array = laurena::mdl::mdl::serialize(sa);
	testunit::log() << "serialized array = " << serialized_array << std::endl;

	string_array sa2;
	laurena::mdl::mdl::parse(serialized_array, sa2);
	assert(sa2.size() == 3);
	return ;
}

void testMdlParameterArray()
{
std::string s;


	parameter pa;
	pa._name = "name";
	pa._descriptor = td<std::string>::desc();

	s = laurena::mdl::mdl::serialize(pa);
	testunit::log() << "serialized parameter = " << s << std::endl;

	parameter pa2;
	laurena::mdl::mdl::parse(s, pa2);
	assert(pa2._descriptor == td<std::string>::desc());

	parameters pas;
	pas.resize(2);
	pas[0]._name = "name";
	pas[0]._descriptor = td<std::string>::desc();

	pas[1]._name = "age";
	pas[1]._descriptor = td<word16>::desc();

	s = laurena::mdl::mdl::serialize(pas);
	testunit::log() << "serialized parameters = " << s << std::endl;

	parameters pas2;
	laurena::mdl::mdl::parse(s, pas2);
	assert(pas2.size() == 2);

	return;
}

void testMdl()
{
    testBasicMdlSerialization();
	testMdlArray();
	testMdlParameterArray();
}
