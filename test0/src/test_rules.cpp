#include "test0.hpp"
#include <laurena/grammar/rule.hpp>

void testRuleStaticChar()
{
	laurena::rule_static_char<> rW ('H');


	const char* cc = "Hello World";
	laurena::rule_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rW.read(context);
	assert(res==1);

}


void testRules()
{
	testRuleStaticChar();
}

