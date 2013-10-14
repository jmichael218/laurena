///
/// \file     rule_basic.hpp
/// \brief    basic interface to implement for all rules
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   grammar rulesbasic interface to implement for all rules
///

#ifndef LAURENA_RULE_BASIC_H
#define LAURENA_RULE_BASIC_H

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

#include <laurena/types/parsing_context.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_basic                                                */ 
/*                                                                              */ 
/********************************************************************************/ 

template <typename CONTEXT = parsing_context<>>	class rule_ptr;

// This is the interface for all rules
template 
<	
	typename CONTEXT = parsing_context<>
>

class rule_basic
{
public:


	/****************************************************************************/ 
	/*			typedef         												*/ 
	/****************************************************************************/ 
	typedef typename CONTEXT::chartype			chartype;

	/****************************************************************************/ 
	/*			constructor     												*/ 
	/****************************************************************************/ 
	rule_basic() { }


	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int	read (CONTEXT& context)		 const =0;
	virtual void                regexp(std::ostream& out)    const =0;

	virtual bool  is_candidate(chartype c) const
	
		{ return false; }

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
