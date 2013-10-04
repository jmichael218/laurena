///
/// \file     rule_expected_char.hpp
/// \brief    a rule to read a single expected character
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   a rule to read a single expected character

#ifndef LAURENA_RULE_EXPECTED_CHAR_H
#define LAURENA_RULE_EXPECTED_CHAR_H

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


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_expected_char                                        */ 
/*                                                                              */ 
/********************************************************************************/ 

template 
<
	typename CHARTYPE =char, 
	typename CONTEXT = parsing_context<>
>

class rule_expected_char : public rule_templated<CHARTYPE, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 

	rule_expected_char(CHARTYPE charExpected) 
		
		: rule_templated<CHARTYPE, CONTEXT>(), 
		  _value(charExpected)

		{ }

	/****************************************************************************/ 
	/*			implementation of virtual functions 							*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		if (*context._first == this->_value)
		{			
			context.count(*context._first);
			this->readed(this->_value,context);
			return 1;
		}
		return pec::SYNTAX_ERROR;
	}

	virtual void regexp(std::ostream& out)    const

		{ out << this->_value; }

	virtual bool  is_candidate(chartype c)  const
	{ 
		return (c == this->_value);
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	
	CHARTYPE _value;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
