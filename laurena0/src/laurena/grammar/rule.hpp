///
/// \file     rules.hpp
/// \brief    grammar rules
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   grammar rules
///

#ifndef LAURENA_RULES_H
#define LAURENA_RULES_H

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

#include <laurena/grammar/rule_builder.hpp>
#include <laurena/grammar/rule_table.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

template<
	
	typename CONTEXT=parsing_context<>
>

class rule : public rule_basic<CONTEXT>
{
public:

	/****************************************************************************/
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef typename CONTEXT::chartype										chartype;

	/****************************************************************************/ 
	/*			constructors													*/ 
	/****************************************************************************/ 
	
	rule() 
		
		: rule_basic<CONTEXT>() 
		{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 

	virtual unsigned long int read (CONTEXT& context) const
	{ 
		return this->_rules.read(context); 
	}

	virtual void  regexp(std::ostream& out)    const
	{
		for (const rule_ptr<CONTEXT>& r : this->_rules)
			r->regexp(out);
	}

	virtual bool  is_candidate(chartype c) const
	{ 
		return this->_rules.size() ? this->_rules.front()->is_candidate(c) : false;
	}


	/****************************************************************************/ 
	/*			construction of the rule										*/ 
	/****************************************************************************/ 

	rule<CONTEXT>& operator<<(rule_ptr<CONTEXT>& r)
	{
		_rules.push_back(r);
		return *this;
	}

	template<typename T>
	rule<CONTEXT>& operator<<(rule_templated<T, CONTEXT>* r)
	{
		_rules.push_back(rule_ptr<CONTEXT>(r));
		return *this;
	}


	inline
	rule<CONTEXT>& operator << (chartype value)
	{
		return *this << rule<CONTEXT>::char_(value);
	}

	inline 
	rule<CONTEXT>& operator << (const charset<chartype>& cset )
	{
		return *this << rule<CONTEXT>::set_(cset);
	}


	template<typename T>
	rule<CONTEXT>& operator<< (std::function<void (const T&, typename CONTEXT::object)> cb)
	{
		rule_templated<T, CONTEXT>* r = dynamic_cast<rule_templated<T, CONTEXT>*>(this->_rules.back().get());
		r->operator [](cb);
		return *this;
	}


	/****************************************************************************/ 
	/*			protected datas													*/ 
	/****************************************************************************/ 
	protected:
	rule_table<CONTEXT>		_rules;
} ;



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif