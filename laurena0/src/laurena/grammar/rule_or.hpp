///
/// \file     rule_or.hpp
/// \brief    rules implemeting a selection between several other rules
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules implemeting a selection between several other rules

#ifndef LAURENA_RULE_OR_H
#define LAURENA_RULE_OR_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <memory>
#include <ostream>

#include <laurena/grammar/rule_table.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_integer                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename CONTEXT=parsing_context<>			 // context
>

class rule_or : public rule_basic<CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors													*/ 
	/****************************************************************************/ 
	
	rule_or() 
		
		: rule_basic<CONTEXT>() 
		{ }


	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 

	virtual unsigned long int read (CONTEXT& context) const
	{ 
		if (this->_rules.size() == 0)
			return pec::SYNTAX_ERROR;

		unsigned int candidates = 0;
		rule_table<CONTEXT>::const_iterator it_candidate;
		chartype c = *context._first;
		for (auto it = this->_rules.begin(); it != this->_rules.end(); it ++)
		{
			if (it->get()->is_candidate(c))
			{
				candidates ++;
				it_candidate = it;
			}
		}
		if (candidates == 1)
			return it_candidate->get()->read(context);
		else
			return pec::SYNTAX_ERROR;
	}

	virtual void  regexp(std::ostream& out)    const
	{
		if (this->_rules.size())
		{
			out << "(";
			bool first = true;
			for (const rule_ptr<CONTEXT>& r : this->_rules)
			{
				if (first)
					first = false;
				else
					out << "|";
				r->regexp(out);
			}
			out << ")";
		}
	}

	virtual bool  is_candidate(chartype c) const
	{ 
		for (const rule_ptr<CONTEXT>& r : this->_rules)
			if (r->is_candidate(c))
				return true;

		return false;
	}


	/****************************************************************************/ 
	/*			construction of the rule										*/ 
	/****************************************************************************/ 

	rule_or<CONTEXT>& operator | (rule_ptr<CONTEXT>& r)
	{
		_rules.push_back(r);
		return *this;
	}

	rule_or<CONTEXT>& operator |= (rule_ptr<CONTEXT>& r)
	{
		_rules.push_back(r);
		return *this;
	}


	/****************************************************************************/ 
	/*			protected datas													*/ 
	/****************************************************************************/ 
	protected:
	rule_table<CONTEXT>		_rules;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file