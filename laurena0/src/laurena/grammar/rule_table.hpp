///
/// \file     rule_table.hpp
/// \brief    a vector of rule_ptr
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   a vector of rule_ptr
///

#ifndef LAURENA_RULE_TABLE_H
#define LAURENA_RULE_TABLE_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <memory>
#include <ostream>
#include <vector>

#include <laurena/grammar/rule_ptr.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_table                                                */ 
/*                                                                              */ 
/********************************************************************************/ 

// This is a vector of rule_ptr
template 
<
	typename CONTEXT = parsing_context<>
>

class rule_table : public std::vector<rule_ptr<CONTEXT>>
{
public:

	/************************************************************************/ 
	/*		constructor														*/ 
	/************************************************************************/ 

	rule_table () { };
	rule_table (rule_table&& r) 
		
		: std::vector<std::unique_ptr<rule_basic<CONTEXT>>> (r)
		{ }

	/************************************************************************/ 
	/*		rule execution													*/ 
	/************************************************************************/ 

	unsigned long int read(CONTEXT& context) const
	{
		unsigned long int res = 0, r2;
		for (const rule_ptr<CONTEXT>& r : *this)
		{
			r2 = r->read(context);

			if (r2 == 0 || r2 == pec::SYNTAX_ERROR)
				return pec::SYNTAX_ERROR;

			context._first = CONTEXT::traits::readed(context._first, r2);
			res += r2;
		}
		return res;
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
