#include "test0.hpp"
#include <laurena/algorithm/strings/readwhile.hpp>


void testReadWhile()
{
	const char* s0 = "hello world";
	laurena::charset<> cs ("hel");

	std::string s = laurena::readwhile(s0,cs);
	assert(s == "hell");

	std::istringstream ss;
	ss.str("hello world");
	std::string s2 = laurena::readwhile(ss,cs);
	assert(s2 == "hell");

}
//End of file
