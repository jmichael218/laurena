///
/// \file     rule_charset.hpp
/// \brief    rules based on a charset condition (while in charset, until in charset ... )
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules based on a charset condition (while in charset, until in charset ... )

#ifndef LAURENA_RULE_CHARSET_H
#define LAURENA_RULE_CHARSET_H

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
#include <laurena/algorithm/strings/readwhile.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_charset                                              */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename STRING=std::basic_string<char>, 
	typename CHARSET=charset<char>, 
	typename CONTEXT=parsing_context<>
>

class rule_charset : public rule_string<STRING, CONTEXT>
{
public:

	/****************************************************************************/
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef typename CONTEXT::iterator										iterator;
	typedef std::function<STRING (iterator, iterator, const typename CHARSET::test_function &)>		algorithm;

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 

	rule_charset(const CHARSET& cset,  algorithm pfun = readwhile<iterator, typename CHARSET::chartype, STRING>) 
		
		: rule_string<STRING, CONTEXT>(), 
		  _charset(cset),
		  _algorithm(pfun)

		{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 

	virtual unsigned long int read (CONTEXT& context) const
	{
		STRING ss = std::move(this->_algorithm(context._first, context._last,this->_charset.condition()));
		if (ss.length() == 0)
			return pec::SYNTAX_ERROR;
		else
		{
			context.count(ss);
			this->readed(ss,context);
			return ss.length();
		}
	}

	virtual void  regexp(std::ostream& out)    const
	{
		out << "[" << this->_charset.characters () << "]*";
	}

	virtual bool  is_candidate(chartype c) const
	{ 
		return this->_algorithm(&c, (&c)+1, this->_charset.condition()).length() == 1;
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	
	const CHARSET _charset;
	algorithm	  _algorithm;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
