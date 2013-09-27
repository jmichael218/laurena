#include "test0.hpp"
#include <laurena/grammar/rule.hpp>
#include <laurena/constants/const_charsets.hpp>

void testRuleStaticChar()
{
	laurena::rule_static_char<> rW ('H');

	rW [ [] (const char& c, laurena::rule_context<>::object o) { std::cout <<"*" << c << "*" << std::endl ; } ];

	const char* cc = "Hello World";
	laurena::rule_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rW.read(context);
	assert(res==1);

}

void testRuleCharset()
{
	laurena::rule_template<std::string, laurena::rule_context<>>::callback_read_type cb =  [] (const std::string& s, int c) { std::cout << s;};
	laurena::rule_charset<> pnumbers (laurena::const_charsets<>::NUMBERS);
	pnumbers.cbread(cb);
	const char* cc = "123456blabla";
	laurena::rule_context<> context (cc, cc+strlen(cc));
	unsigned long int res = pnumbers.read(context);
	assert(res==6);
}

void testRuleAddition()
{
	laurena::rules<> rs ;
	rs << laurena::rule<>::char_('H') << laurena::rule<>::char_('e');

	const char* cc = "Hello World";
	laurena::rule_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res==2);

	laurena::rules<> rs2;


	laurena::rule_template<char, laurena::rule_context<>>::callback_read_type  printchar = [] (const char& c, laurena::rule_context<>::object o) { std::cout << c; };
	laurena::rule_template<std::string, laurena::rule_context<>>::callback_read_type printstr  = [] (const std::string& s, laurena::rule_context<>::object i ) { std::cout << s; };


	rs2 << laurena::rule<>::char_('(')				[[] (const char& c, laurena::rule_context<>::object o) { std::cout << c; }]
		<< laurena::rule<>::set_(laurena::const_charsets<>::NUMBERS)		[[] (const std::string& s, laurena::rule_context<>::object i ) { std::cout << s; }]
		<< laurena::rule<>::char_(',')				[[] (const char& c, laurena::rule_context<>::object o) { std::cout << c; }]
		 << laurena::rule<>::set_(laurena::const_charsets<>::NUMBERS)		[[] (const std::string& s, laurena::rule_context<>::object i ) { std::cout << s; }]
		 << laurena::rule<>::char_(')')             [[] (const char& c, laurena::rule_context<>::object o) { std::cout << c; }]
		 ;

	const char* cc2 = "(1234,56788)";
	laurena::rule_context<> context2 (cc2, cc+strlen(cc2));
	res = rs2.read(context2);
	assert(res == 12);

}

void testRules()
{
	testRuleStaticChar();
	testRuleCharset();
	testRuleAddition();
}

