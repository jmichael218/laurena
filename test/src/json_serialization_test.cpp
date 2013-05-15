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

void testJson()
{
    testBasicJsonSerialization();
}
