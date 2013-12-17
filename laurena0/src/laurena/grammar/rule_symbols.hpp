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
/*			forward definition													*/ 
/********************************************************************************/ 
template
<
	typename KEY,							// key type of the symbols
	typename VALUE,							// value type of the symbols
	typename CONTEXT=parsing_context<>			// context
>

class rule_symbols;

/********************************************************************************/ 
/*			implementation of rule_symbols::read								*/ 
/********************************************************************************/ 

// empty implementation for failed substitution
template
<
	bool ENABLED_CHARTYPE, bool ENABLED_STRINGTYPE

	,typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
	,typename CONTEXT		// context	
>
struct rule_symbols_implementation
{
};

// implementation when KEY is a chartype
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
	,typename CONTEXT		// context
		
>
struct rule_symbols_implementation<true, false, KEY, VALUE, CONTEXT>
{

	/*******************************************************************************/ 
	/*			typedefs for readability										   */ 
	/*******************************************************************************/ 
	typedef typename CONTEXT::chartype			chartype;
	typedef rule_symbols<KEY, VALUE>			ruletype;
	typedef symbols<KEY, VALUE>					symbolstype;

	/****************************************************************************/ 
	/*		implementation of the read function									*/ 
	/****************************************************************************/ 

	// implementation for KEY = CHARTYPE
	static inline
	unsigned long int read(const ruletype& therule, CONTEXT& context)
	{
		const symbolstype& s = therule.values();
		auto it = s.key(*context._first);
		if (it == s.end())
		{ return pec::SYNTAX_ERROR; }

		context.count(*context._first);
		therule.readed(it->second,context);
		return 1;
	}

	static inline 
	bool is_candidate (const ruletype& therule, chartype c )
	{
		return therule.values().key(c) != therule.values().end();
	}
};

// implementation when KEY is a std::basic_string<chartype> class
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
	,typename CONTEXT		// context

>
struct rule_symbols_implementation<false, true, KEY, VALUE, CONTEXT>
{

	/*******************************************************************************/ 
	/*			typedefs for readability										   */ 
	/*******************************************************************************/ 
	typedef typename CONTEXT::chartype						chartype;
	typedef rule_symbols<KEY, VALUE>						ruletype;
	typedef symbols<KEY, VALUE>								symbolstype;
	typedef typename symbols<KEY, VALUE>::const_iterator	iterator;

	/****************************************************************************/ 
	/*		implementation of the read function									*/ 
	/****************************************************************************/ 

	static inline
	unsigned long int read(const ruletype& therule, CONTEXT& context)
	{
		KEY sresult;
		unsigned long int nb_candidates;
		auto it = context._first;
		const symbolstype& s = therule.values();

		while (it != context._last)
		{
			sresult += *it++;
			nb_candidates = s.candidates(sresult);

			if (nb_candidates == 0)
				return pec::SYNTAX_ERROR;

			if (nb_candidates == 1)
			{
				auto itres = s.key(sresult);	
				if (itres != s.end())
				{				
					context.count(sresult);
					therule.readed(itres->second,context);
					return sresult.length();
				}
			}
		}
		return pec::SYNTAX_ERROR;
	}


	static inline 
	bool is_candidate (const ruletype& therule, chartype c )
	{
		KEY sresult;
		sresult += c;
		return therule.values().candidates(sresult) > 0;
	}
	
};

// tag dispatcher for the implementation
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
	,typename CONTEXT		// context
>
struct rule_symbols_implementation_dispatch 
	
	: public rule_symbols_implementation
	<
		std::is_same<KEY, typename CONTEXT::chartype>::value
		,std::is_same<KEY, std::basic_string<typename CONTEXT::chartype>>::value
		,KEY
		,VALUE
		,CONTEXT
	>

	{ }
;
/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_symbols                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename KEY,							// key type of the symbols
	typename VALUE,							// value type of the symbols
	typename CONTEXT						// context
>

class rule_symbols : public rule_templated<VALUE, CONTEXT>
{
public:

	/*******************************************************************************/ 
	/*			typedefs for readability										   */ 
	/*******************************************************************************/ 
	typedef typename CONTEXT::chartype						chartype;

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
		return rule_symbols_implementation_dispatch<KEY, VALUE, CONTEXT>::read(*this, context);
	}

	virtual void  regexp(std::ostream& out)    const
	{ this->_symbols.regexp(out); }

	virtual bool is_candidate(chartype c) const
	{
		return false;
	}

	/****************************************************************************/ 
	/*			getters / setters												*/ 
	/****************************************************************************/ 
	inline 
	const symbols<KEY, VALUE>& values () const 

	{
		 return this->_symbols;
	}
	/****************************************************************************/ 
	/*			protected datas													*/ 
	/****************************************************************************/ 
	protected:

	const symbols<KEY, VALUE>&		_symbols;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
