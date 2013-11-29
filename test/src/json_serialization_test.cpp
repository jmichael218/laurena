///
/// \file     json_serialization_test.cpp
/// \brief    test functions for the json language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// test functions for the json language
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace json;

#include <boost/spirit/include/qi.hpp>

void testBasicJsonSerialization ()
{
    character bob;
    bob._name = "Bob" ;
    bob._age = 28;

    testunit::type("JSON - simple object");
    testunit::function("oarchive_json::toString + iarchive_json::fromString - simple object");

    std::string serialized_bob;
    laurena::json::json::serialize(serialized_bob, "character", &bob);

    testunit::log() << serialized_bob << std::endl;

    character bob2;
    laurena::json::json::parse(serialized_bob,"character",bob2);
    
    testunit::endTest(bob2._name == "Bob" && bob2._age == 28 );

	testunit::function("oarchive_json::toString + iarchive_json::fromString - object with sub object");
	character marie ;
	marie._name = "marie";
	marie._age = 26;

	mariage m;
	m._husband = &bob;
	m._wife = &marie;

	character kevin;
	kevin._name = "kevin";
	kevin._age = 4;
	m._children.push_back(&kevin);

	character britney;
	britney._name = "britney";
	britney._age = 6;
	m._children.push_back(&britney);

	character joss;
	joss._name = "joss";
	joss._age = 8 ;
	m._children.push_back(&joss);

	std::string serialized_mariage;
	laurena::json::json::serialize(serialized_mariage,"mariage",&m);
	testunit::log() << serialized_mariage << std::endl;

	mariage m2 ;
	laurena::json::json::parse(serialized_mariage,"mariage",m2);

	testunit::endTest(m2._husband->_name == "Bob" && m2._husband->_age == 28 && m2._wife->_name == "marie" && m2._wife->_age == 26);


    return;
}

void testJsonlList ()
{
	const descriptor* lwdesc = list_descriptor<LWord32, word32>::build("lword32");
	LWord32 lw;
	lw.push_back(65);
	lw.push_back(486);
	lw.push_back(-4);

	std::string s = laurena::json::json::serialize(lw, laurena::json::json::COMPACT);
	std::cout << s << std::endl;

	LWord32 lw2;
	laurena::json::json::parse(s, lw2);

	const descriptor* lsdesc  = list_descriptor<LString, std::string>::build("lstring");
	LString ls;
	ls.push_back("hello");
	ls.push_back("world");

	s = laurena::json::json::serialize(ls, laurena::json::json::COMPACT);
	std::cout << s << std::endl;

	LString ls2;
	laurena::json::json::parse(s, ls2);

	return;
}

void testJSonNoWrapper()
{
	character bob;
    bob._name = "Bob" ;
    bob._age = 28;

    testunit::type("JSON - simple object no wrapper");
    testunit::function("oarchive_json::toString + iarchive_json::fromString - simple object");

    std::string serialized_bob  = laurena::json::json::serialize(bob, laurena::json::json::NO_WRAPPER);

    testunit::log() << serialized_bob << std::endl;
}

void testJsonAny()
{

	// test int
	variable a;
	a._value = (word32) 5;
	a._name = "age";
    std::string s  = laurena::json::json::serialize(a);
    testunit::log() << s << std::endl;

	variable b;
	laurena::json::json::parse(s, b);

	assert(anycast<int64>(b._value) == 5);

	// test string
	a._value = "Red John";
	a._name = "name";

    s  = laurena::json::json::serialize(a);
    testunit::log() << s << std::endl;

	laurena::json::json::parse(s, b);

	assert(anycast<std::string>(b._value) == "Red John");


	// test boolean
	a._name = "alive";
	a._value = true;

    s  = laurena::json::json::serialize(a);
    testunit::log() << s << std::endl;

	laurena::json::json::parse(s, b);

	assert(anycast<bool>(b._value) == true);

	return;

}

void testJson()
{
    testBasicJsonSerialization();
	testJsonlList();
	testJSonNoWrapper();
	testJsonAny();
}
