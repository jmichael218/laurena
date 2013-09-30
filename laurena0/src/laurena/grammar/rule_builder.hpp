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

#include <laurena/grammar/rule.hpp>
#include <laurena/grammar/rule_expected_char.hpp>
#include <laurena/grammar/rule_charset.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>

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

	/*******************************************************************************/ 
	/*					rules builders											   */ 
	/*******************************************************************************/ 
	static rule_ptr_templated<chartype, CONTEXT> expected_ (chartype value)
	{
		return rule_ptr_templated<chartype, CONTEXT> (new rule_expected_char<chartype, CONTEXT>(value));
	}

	static rule_ptr_templated<string, CONTEXT> while_ (const characters& cset)
	{
		auto p = new rule_charset<string, characters>(cset);
		return rule_ptr_templated<string, CONTEXT> (p);
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file