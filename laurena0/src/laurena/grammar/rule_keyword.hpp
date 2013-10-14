///
/// \file     rule_keyword.hpp
/// \brief    rule expecting a given keyword
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rule expecting a given keyword

#ifndef LAURENA_RULE_KEYWORD_H
#define LAURENA_RULE_KEYWORD_H

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

#include <laurena/grammar/rule_string.hpp>
#include <laurena/algorithm/strings/prefix.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_keyword                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename CONTEXT=parsing_context<>
>
class rule_keyword : public rule_string<std::basic_string<typename CONTEXT::chartype>, CONTEXT>
{
public:

	/****************************************************************************/
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef typename CONTEXT::iterator										iterator;
	typedef typename std::basic_string<typename CONTEXT::chartype>			string;
	typedef typename CONTEXT::chartype										chartype;

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 

	rule_keyword(const string& keyword) 

		: rule_string<string, CONTEXT>(), 
		_value(keyword)

	{ }

	rule_keyword(const chartype* keyword) 

		: rule_string<string, CONTEXT>(), 
		_value(keyword)

	{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		if (prefix<iterator, const chartype*>(context._first, this->_value.data(), this->_value.data() + this->_value.length()))
		{			
			context.count(this->_value);
			this->readed(this->_value,context);
			return this->_value.length();
		}
		return pec::SYNTAX_ERROR;
	}

	virtual void regexp(std::ostream& out)    const

	{ out << this->_value; }

	virtual bool  is_candidate(chartype c)  const
	{ 
		return (c == this->_value.front());
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	string _value;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
