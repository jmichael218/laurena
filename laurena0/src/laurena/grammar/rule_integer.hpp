///
/// \file     rule_integer.hpp
/// \brief    rules to read an integer
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules to read an integer

#ifndef LAURENA_RULE_INTEGER_H
#define LAURENA_RULE_INTEGER_H

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

#include <boost/lexical_cast.hpp>

#include <laurena/grammar/rule_templated.hpp>
#include <laurena/algorithm/strings/readinteger.hpp>


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
	typename NUMTYPE=int, // returned string type
	typename CONTEXT=parsing_context<>			 // context
>

class rule_integer : public rule_templated<NUMTYPE, CONTEXT>
{
public:

	/****************************************************************************/
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef typename CONTEXT::chartype							chartype;
	typedef typename CONTEXT::iterator							iterator;
	typedef std::basic_string<typename CONTEXT::chartype>		string;

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_integer() : rule_templated<NUMTYPE, CONTEXT>() 
	{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		string ss = std::move(readinteger<chartype, iterator, string>(context._first, context._last));
		if (ss.length() == 0)
			return pec::SYNTAX_ERROR;
		else
		{
			context.count(ss);
			this->readed(boost::lexical_cast<NUMTYPE, string>(ss),context);
			return ss.length();
		}
	}

	virtual void regexp(std::ostream& out)    const

		{ out << "[-]?[0123456789]*"; }
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file