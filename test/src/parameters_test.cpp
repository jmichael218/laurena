///
/// \file     parameters_test.cpp
/// \brief    Test parameter & parameters classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test parameter & parameters classes
//
#include <laurena/laurena.hpp>

using namespace laurena;

void testParametersSyntax()
{
	parameters ps;
	bool ok = ps.syntax("keyword name keyword password word16 age *keyword gender *string message");
	assert(ok);
	assert(ps.size() == 5);

	context cnt;
	std::string ss = "Bob Joe 34 male Yé yé yé!" ;
	ps.parse(cnt, ss);


	return;
}


void testParameters()
{
	testParametersSyntax();
}