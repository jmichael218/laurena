#include "test0.hpp"
#include <laurena/algorithm/strings/alphabet.hpp>


void testAlphabet()
{
	const char* s1 = "hello world";
	std::string s2 = "hello world";
	std::string expected = "helo wrd";
	std::string r0 = laurena::alphabet<const char*, std::string>(s1, s1+strlen(s1));

	assert(r0 == expected);

	std::string r1 = laurena::alphabet(s1);
	assert(r1 == expected);

	std::string r2 = laurena::alphabet(s2);
	assert(r2 == expected);

	std::istringstream ss;
	ss.str(s2);
	std::string r3 = laurena::alphabet(ss);
	assert(r3 == expected);


}
//End of file
