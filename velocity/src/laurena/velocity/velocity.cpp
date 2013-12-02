///
/// \file     velocity.cpp
/// \brief    Main file to include to use the Velocity language as script language for output.
/// \author   Frederic Manisse
/// \version  1.0
///
/// \brief    Main file to include to use the Velocity language as script language for output.
///
#include <laurena/velocity/velocity.hpp>
#include <laurena/algorithm/strings/readuntil.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

laurena::charset<> velo_alphabet ("#$");

const char* velocity::skipComment(const char* src)
{
	while(true)
	{
		while (*src && (*src != '*')) ++ src;

		if (!*src) 
			return src;

		// else *src == '*'
		++ src;
		if (*src == '#')
			return ++src;				

	}
	return src;
}

const char* velocity::skipSingleLineComment(const char* src)
{
	while(true)
	{
		while (*src && (*src != '\n')) ++ src;

		if (!*src) 
			return src;

		// else *src == '*'
		return ++ src;
	}
	return src;
}

const char* velocity::handleSharpCharacter(const char* src, std::ostream& output)
{
	switch (*src)
	{
		case '*' : // comment
			src = this->skipComment(src);
			break;
		case '#' : // single line comment
			src = this->skipSingleLineComment(src);
			break;

	}
	output << "#" ;
	return src;
}

const char* velocity::handleDollarCharacter(const char* src, std::ostream& output)
{
	std::string varname = laurena::readwhile(src,const_charsets<>::VARNAME.condition());
	if (varname.length() == 0)
		return src;

	src += varname.length();
	
}

std::string velocity::render(const std::string& source)
{
std::ostringstream ss;
const char* src = source.c_str();
std::string readed;


	while(*src)
	{
		readed = laurena::readuntil(src,velo_alphabet.condition());
		ss << readed;
		src += readed.length();
		if (velo_alphabet.test(*src))
		{
			if (*src == '#')
				src = this->handleSharpCharacter(src, ss);
			else if (*src == '$')
				src = this->handleDollarCharacter(src, ss);
			}
		}
	}

	return ss.str();
}
