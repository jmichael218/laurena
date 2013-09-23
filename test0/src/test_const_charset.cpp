#include "test0.hpp"
#include <laurena/constants/const_charsets.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>


void testConstCharSets()
{
	// RN
	std::string s = "hello\r\nworld";
	std::string r = laurena::readwhile(s,laurena::const_charsets<>::RN);
	assert(r=="hello");

	std::wstring w = L"hello \r\nworld";
	std::wstring r2 = laurena::readwhile(w,laurena::const_charsets<wchar_t>::RN);
	assert(r2==L"hello");

}
