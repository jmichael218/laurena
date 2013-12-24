///
/// \file     time.cpp
/// \brief    A toolbox of functions for time related operations
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for time related operations
///
#include <laurena/toolboxes/time.hpp>

using namespace laurena;

typedef laurena::rule_builder<laurena::parsing_context<>> G;

word64 Time::parse(const std::string& format, const std::string& value, word32* len_parsed)
{
	const char* s = value.c_str();
	return 0;
}

std::shared_ptr<laurena::rule<>> Time::generate_rule(const std::string& format)
{
	std::shared_ptr<laurena::rule<>> r = std::make_shared<laurena::rule<>>();
	const char* s = format.c_str();

	rule_ptr<> rp;

	if (!s)
		return r;

	while (*s)
	{
		switch(*s)
		{
			case '%':
				s++;
				switch(*s)
				{

				}
				break;
			default:
				rp = G::expected_(*s);
				r->operator<<(rp);
				break;

		}
	}
}
