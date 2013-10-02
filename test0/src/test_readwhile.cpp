#include "test0.hpp"
#include <laurena/algorithm/strings/readwhile.hpp>
#include <laurena/types/charset.hpp>


void testReadWhile()
{

	const char* s0 = "hello world";
	std::string expected = "hell";
	laurena::charset<> cs ("hel");

	std::string s = laurena::readwhile(s0,cs.condition());
	assert(s == expected);

	std::string s1 = s0;
	s = laurena::readwhile(s1, cs.condition());
	assert(s == expected);

	std::istringstream ss;
	ss.str("hello world");
	// <typename CHARTYPE, typename ISTREAM, typename ISTREAM_ITERATOR, typename STRING>
	std::string s2 = laurena::readwhile(ss,cs.condition());
	assert(s2 == expected);


}
//End of file
