///
/// \file     rule_symbols.hpp
/// \brief    rules to read a symbol and cast it into a real value
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules to read a symbol and cast it into a real value

#ifndef LAURENA_RULE_SYMBOLS_H
#define LAURENA_RULE_SYMBOLS_H

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

#include <laurena/grammar/rule_templated.hpp>
#include <laurena/types/symbols.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*			implementation of rule_symbols::read								*/ 
/********************************************************************************/ 

// implementation for KEY = CHARTYPE
template
<
	typename KEY,							// key type of the symbols
	typename VALUE,							// value type of the symbols
	typename CONTEXT=rule_context<>,		// context
	typename ENABLED= typename std::enable_if<std::is_same<KEY, CONTEXT::chartype>::value>::type
>
struct rule_symbols_implementation
{

	static
	unsigned long int read(const rule_templated<VALUE, CONTEXT>& therule, CONTEXT& context, const symbols<KEY, VALUE>& s)
	{
		auto it = s.key(*context._first);
		if (it == s.end())
		{ 	return pec::SYNTAX_ERROR; }

		context.count(*context._first);
		therule.readed(it->second,context);
		return 1;
	}
};

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_symbols                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename KEY,							// key type of the symbols
	typename VALUE,							// value type of the symbols
	typename CONTEXT=parsing_context<>			// context
>

class rule_symbols : public rule_templated<VALUE, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_symbols(const symbols<KEY, VALUE>& ref_symbols) 
		
		: rule_templated<VALUE, CONTEXT>()
		, _symbols(ref_symbols)

	{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 

	virtual unsigned long int read (CONTEXT& context) const
	{
		return rule_symbols_implementation<KEY, VALUE, CONTEXT>::read(*this, context, this->_symbols);
	}

	virtual void  regexp(std::ostream& out)    const
	{ this->_symbols.regexp(out); }

	/****************************************************************************/ 
	/*			protected datas													*/ 
	/****************************************************************************/ 
	protected:

	const symbols<KEY, VALUE>&		_symbols;

};




// implementation for KEY = std::basic_string<CHARTYPE>
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
