#include "test0.hpp"
#include <laurena/algorithm/strings/readinteger.hpp>


void testReadInteger()
{
	
	std::string s0 = "-45jjhhs";
	std::string r0 = laurena::readinteger(s0);
	assert(r0 == "-45");


	std::istringstream ss;
	ss.str("-368fdkek");
	std::string s2 = laurena::readinteger(ss);
	assert(s2 == "-368");

}
//End of file
