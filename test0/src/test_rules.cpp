#include "test0.hpp"
#include <laurena/grammar/rule.hpp>
#include <laurena/constants/const_charsets.hpp>
#include <laurena/algorithm/strings/readuntil.hpp>

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
	context._output = &std::cout;

	unsigned long int res = pnumbers.read(context);
	assert(res==6);

	laurena::charset<> csetB ("b");
	laurena::rule_charset<>pwaitb (csetB, laurena::readuntil<const char*, char, std::string>);
	laurena::parsing_context<> context2 (cc, cc+strlen(cc));
	context2._output = &std::cout;

	res = pwaitb.read(context2);
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

void testRuleSymbols()
{
	typedef std::pair<char, bool> sss;
	sss S[2] =  { sss('T', true), sss('F', false)}; 
	laurena::symbols<char,bool> truefalse (S);
	laurena::rule_symbols<char,bool> rsymbs (truefalse);

	std::function<void (const bool& b, laurena::parsing_context<>::object i )> bcb 
		
		= [] (const bool& b, laurena::parsing_context<>::object) { std::cout << (b?"<TRUE>":"<FALSE>"); };

	laurena::rule<> rs;
	rs << G::symbols_(truefalse) [bcb]
	   << G::symbols_(truefalse) [bcb]
	   << G::symbols_(truefalse) [bcb]
	   << G::symbols_(truefalse) [bcb]
	   ;

	const char* cc = "TFTF";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res==4);


	typedef std::pair<std::string, int> day;
	day DAYS [7] = { day("lundi",0), day("mardi",1), day("mercredi",2), day("jeudi",3), day("vendredi",4), day("samedi",5), day("dimanche",6)};
	laurena::symbols<std::string, int> sdays (DAYS);
	laurena::rule_symbols<std::string, int> rdays (sdays);

	laurena::rule <> rs2;

	std::function<void (const int& b, laurena::parsing_context<>::object i )> sib

		= [] (const int& b, laurena::parsing_context<>::object) { std::cout << "J" << b; };

	rs2 << G::symbols_(sdays) [sib]
		<< G::symbols_(sdays) [sib]
		<< G::symbols_(sdays) [sib]
		<< G::symbols_(sdays) [sib]
		;

	const char* cc2="lundimardimercredidimanche";
	laurena::parsing_context<> context2 (cc2, cc+strlen(cc2));
	res = rs2.read(context2);
	assert(res == strlen(cc2));


}


void testRuleInteger ()
{
	laurena::rule_integer<int, laurena::parsing_context<>> ri ;

	laurena::rule<> rs;

	rs << G::expected_('(')			[[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		<< G::num_<int>()			[[] (const int& s, laurena::parsing_context<>::object i ) { std::cout << s; }]
		<< G::expected_(',')		[[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		 << G::num_<int>()			[[] (const int& s, laurena::parsing_context<>::object i ) { std::cout << s; }]
		 << G::expected_(')')       [[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }]
		 ;

	const char* cc = "(12,15)";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res == strlen(cc));
}


void testRuleKeyword ()
{
	laurena::rule_keyword<> rk ("hello");
	
	laurena::rule<> rs;

	rs << G::kword_("hello")		[[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }]
	   << G::kword_("world")		[[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }]
	   ;

	const char* cc = "helloworld";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res == strlen(cc));

}

void testRuleOr ()
{
	laurena::rule_or<>* rk = new laurena::rule_or<>();

	laurena::rule<> rs;

	(*rk) | G::kword_("hello") [[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }] 
	   | G::kword_("bonjour") [[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }]
	   | G::kword_("priviet") [[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }]
	   ;
	   

	rs << laurena::rule_ptr<>(rk) 
	   << G::expected_(' ') [[] (const char& c, laurena::parsing_context<>::object o) { std::cout << c; }] 
	   << G::kword_("world") [[] (const std::string& c, laurena::parsing_context<>::object o) { std::cout << c; }];

	const char* cc = "bonjour world";
	laurena::parsing_context<> context (cc, cc+strlen(cc));
	unsigned long int res = rs.read(context);
	assert(res == strlen(cc));

}

void testRules()
{
	testRuleStaticChar();
	testRuleCharset();
	testRuleAddition();
	testRuleSymbols();
	testRuleInteger();
	testRuleKeyword();
	testRuleOr();

}

