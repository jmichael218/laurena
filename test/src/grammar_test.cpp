///
/// \file     grammar_descriptor_test.cpp
/// \brief    Test grammar types and functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test grammar types and functions
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include <laurena/source/source_location.hpp>
#include <laurena/grammar/rules.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testSourceLocation()
{
	source_location<> src ("testSourceLocation");

	src.count('c');
	src.count('\n');
	src.count("Hello world");
	std::string str = "Winter is coming";
	src.count(str);

	std::cout << "In " << src.filename() << " at line " << src.line() << ", column " << src.column() << std::endl;

}

void testRuleStaticChar ()
{
	source_location<> src (__FUNCTION__);
	std::string str = "Winter is coming";
	rule_static_char<> W ('W');

	any value;
	auto it = str.begin();
	bool ok = W.read(it, it+1, src, value);
	bool nok = W.read(it, it+1, src, value);

	assert(ok && !nok);
}

void testSymbols ()
{
	std::pair<char, bool> qbs [2] = { std::make_pair('[', true), std::make_pair(']', false)};
	symbols<char, bool> qb (qbs);

	auto it0 = qb.value(false);
	assert(it0 != qb.end());


}


void testGrammar()
{
	testSourceLocation ();
	testSymbols();
	testRuleStaticChar();
}
//End of file