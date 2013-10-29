///
/// \file     rule_hexadecimal.hpp
/// \brief    rules to read an integer from an hexadecimal alphabet
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules to read an integer from an hexadecimal alphabet

#ifndef LAURENA_RULE_HEXADECIMAL_H
#define LAURENA_RULE_HEXADECIMAL_H

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
#include <laurena/algorithm/strings/readhexadecimal.hpp>


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

class rule_hexadecimal : public rule_templated<NUMTYPE, CONTEXT>
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
	rule_hexadecimal() : rule_templated<NUMTYPE, CONTEXT>() 
	{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		string ss = std::move(readhexadecimal<chartype, iterator, string>(context._first, context._last));
		if (ss.length() == 0)
			return pec::SYNTAX_ERROR;
		else
		{
			context.count(ss);
			NUMTYPE u = 0;
			for (chartype c : ss)
			{
				u <<= 4;
				u += (c >= chartype('0') &&  c <= chartype('9')) ? (c - chartype('0')) : (10 + c - chartype('A'));
			}
			this->readed(u,context);
			return ss.length();
		}
	}

	virtual void regexp(std::ostream& out)    const

		{ out << "[-]?[0123456789ABCDEF]*"; }

	virtual bool  is_candidate(chartype c) const
	{ 
		return c == ((chartype)'-') || const_charsets<chartype>::HEXADECIMAL.test(c);
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file