#include "test0.hpp"
#include <laurena/types/charset.hpp>


void testCharset()
{
	const char* s1 = "hello world";
	std::string s2 = "hello world";
	std::string alphabet = "helo wrd";
	laurena::charset<> cs (alphabet);
	
	bool b0 = cs.validate(s1);
	assert(b0);

	bool b1 = cs.validate(s1, strlen(s1));
	assert(b1);

	bool b2 = cs.validate(s2);
	assert(b2);

	bool b3 = cs.validate(s2.begin(), s2.end());
	assert(b3);

	bool b4 = cs.validate("Hello Zorld");
	assert(!b4);


}
//End of file
