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
#include "character.hpp"

using namespace laurena;
using namespace test;

template<typename CLASS, typename FIELDTYPE>
void set_field(FIELDTYPE CLASS::*f, CLASS& object, FIELDTYPE& v)
{
	object.*f = v;
}

void testNewFieldInit()
{
	character bob;
	set_field<character, std::string>(&character::_name, bob, std::string("Bob"));
	assert(bob._name == "Bob" );
    return;

}