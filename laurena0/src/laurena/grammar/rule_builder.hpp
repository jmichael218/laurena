///
/// \file     rule_builder.hpp
/// \brief    static class used to build rules
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  static class used to build rules

#ifndef LAURENA_RULE_BUILDER_H
#define LAURENA_RULE_BUILDER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/grammar/rule_expected_char.hpp>
#include <laurena/grammar/rule_charset.hpp>
#include <laurena/grammar/rule_symbols.hpp>
#include <laurena/grammar/rule_integer.hpp>
#include <laurena/grammar/rule_hexadecimal.hpp>
#include <laurena/grammar/rule_keyword.hpp>
#include <laurena/grammar/rule_or.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>
#include <laurena/algorithm/strings/readuntil.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_builder                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename CONTEXT= rule_context<>
>
class rule_builder
{
public:

	/*******************************************************************************/ 
	/*					typedefs												   */ 
	/*******************************************************************************/ 
	typedef rule_ptr_templated<typename CONTEXT::chartype, CONTEXT>			type;		// return type
	typedef std::basic_string<typename CONTEXT::chartype>					string;
	typedef typename typename CONTEXT::chartype								chartype;   // chartype
	typedef charset<typename CONTEXT::chartype>								characters;
	typedef typename CONTEXT::iterator										iterator;

	/*******************************************************************************/ 
	/*					rules builders											   */ 
	/*******************************************************************************/ 
	static rule_ptr_templated<chartype, CONTEXT> expected_ (chartype value)
	{
		return rule_ptr_templated<chartype, CONTEXT> (new rule_expected_char<chartype, CONTEXT>(value));
	}

	static rule_ptr_templated<string, CONTEXT> while_ (const characters& cset)
	{
		auto p = new rule_charset<string, characters>(cset, readwhile<iterator, chartype, string>);
		return rule_ptr_templated<string, CONTEXT> (p);
	}

	static rule_ptr_templated<string, CONTEXT> until_ (const characters& cset)
	{
		auto p = new rule_charset<string, characters>(cset, readuntil<iterator, chartype, string>);
		return rule_ptr_templated<string, CONTEXT> (p);
	}

	template<typename KEY, typename VALUE>
	static rule_ptr_templated<VALUE, CONTEXT> symbols_ (const symbols<KEY, VALUE>& s)
	{
		auto p = new rule_symbols<KEY, VALUE, CONTEXT>(s);
		return rule_ptr_templated<VALUE, CONTEXT>(p);
	}

	template<typename NUMTYPE>
	static rule_ptr_templated<NUMTYPE, CONTEXT> num_ ()
	{
		auto p = new rule_integer<NUMTYPE>();
		return rule_ptr_templated<NUMTYPE, CONTEXT>(p);
	}

	template<typename NUMTYPE>
	static rule_ptr_templated<NUMTYPE, CONTEXT> hex_()
	{
		auto p = new rule_hexadecimal<NUMTYPE>();
		return rule_ptr_templated<NUMTYPE, CONTEXT>(p);
	}

	static rule_ptr_templated<string, CONTEXT> kword_ (const string& keyword)
	{
		auto p = new rule_keyword<CONTEXT>(keyword);
		return rule_ptr_templated<string, CONTEXT>(p);
	}

	static rule_ptr<CONTEXT> or_ ()
	{
		rule_or<CONTEXT>* p = new rule_or<CONTEXT>();
		return rule_ptr<CONTEXT>(p);
	}

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file