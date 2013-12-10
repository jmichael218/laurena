///
/// \file     string_array_descriptor_test.cpp
/// \brief    Test String array serialization
/// \author   Frederic Manisse
/// \version  1.0
///
/// Test String array serialization
//
#include <laurena/laurena.hpp>
#include <laurena/velocity/velocity.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;

void testVelocity()
{
	velocity engine;
	character joe;
	joe._name = "John Doe";
	joe._age = 32;
	engine.context() ["actor"] = variable("actor", &joe);
	engine.context().push("day", std::string("Monday"));

	std::string s = engine.render ("Hello $actor.name#* it should not be displayed*#, how do you do ? You are $actor.age old on this ${day}.");
	std::cout << s << std::endl;
	return;
}
//End of file
