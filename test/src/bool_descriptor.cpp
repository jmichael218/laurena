///
/// \file     any_descriptor_test.cpp
/// \brief    Test numeric type descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test numeric type descriptors
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testBoolDescriptor ()
{
test_bool tb, tb2;
std::string s;

	tb._a = true;
	tb._b = false;
	s = laurena::mdl::mdl::serialize(tb);

	std::cout << s << std::endl;

	laurena::mdl::mdl::parse(s, tb2);

	assert(tb2._a == true && tb2._b == false);

	return;

}
