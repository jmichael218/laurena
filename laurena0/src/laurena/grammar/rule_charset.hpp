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
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 

	rule_charset(const CHARSET& cset) 
		
		: rule_string<STRING, CONTEXT>(), 
		  _charset(cset)

		{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 

	virtual unsigned long int read (CONTEXT& context) const
	{
		STRING ss = std::move(readwhile<CONTEXT::iterator, CHARSET, STRING>(context._first, context._last,this->_charset));
		if (ss.length() == 0)
			return pec::SYNTAX_ERROR;
		else
		{
			context._location.count(ss);
			this->readed(ss,context);
			return ss.length();
		}
	}

	virtual void  regexp(std::ostream& out)    const
	{
		out << "[" << this->_charset.characters () << "]*";
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	
	const CHARSET _charset;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file