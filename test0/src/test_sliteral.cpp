#include "test0.hpp"
#include <laurena/literals/string_literal.hpp>


void testLiteral()
{
	std::string srn = laurena::sliteral<char>("\r\n");
	std::wstring wrn = laurena::sliteral<wchar_t>("\r\n");



}
