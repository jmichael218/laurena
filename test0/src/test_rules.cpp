#include "test0.hpp"
#include <laurena/grammar/rule.hpp>
#include <laurena/constants/const_charsets.hpp>

typedef laurena::rule_builder<laurena::parsing_context<>> G;

void testRuleStaticChar()
{
	laurena::rule_expected_char<> rW ('H');

	rW [ [] (const char& c, laurena::parsing_context<>::object o) { std::cout <<"*" << c << "*" << std::endl ; } ];

	const char* cc = "Hello World";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rW.read(context);
	assert(res==1);

}

void testRuleCharset()
{
	laurena::rule_templated<std::string, laurena::parsing_context<>>::callback_read_type cb =  [] (const std::string& s, int c) { std::cout << s;};
	laurena::rule_charset<> pnumbers (laurena::const_charsets<>::NUMBERS);
	pnumbers [cb];
	const char* cc = "123456blabla";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = pnumbers.read(context);
	assert(res==6);
}



void testRuleAddition()
{
	laurena::rule<> rs ;
	rs << G::expected_('H') << G::expected_('e');

	const char* cc = "Hello World";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res==2);

	laurena::rule<> rs2;

	rs2 << G::expected_('(')				[[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		<< G::while_(laurena::const_charsets<>::NUMBERS)		[[] (const std::string& s, laurena::parsing_context<>::object i ) { std::cout << s; }]
		<< G::expected_(',')				[[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		 << G::while_(laurena::const_charsets<>::NUMBERS)		[[] (const std::string& s, laurena::parsing_context<>::object i ) { std::cout << s; }]
		 << G::expected_(')')             [[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		 ;

	const char* cc2 = "(1234,56788)";
	laurena::parsing_context<> context2 (cc2, cc+strlen(cc2));
	res = rs2.read(context2);
	assert(res == 12);

	std::ostringstream ss;
	rs2.regexp(ss);
	std::cout << "regexp = " << ss.str() << std::endl;

}

void testRules()
{
	testRuleStaticChar();
	testRuleCharset();
	testRuleAddition();

}

