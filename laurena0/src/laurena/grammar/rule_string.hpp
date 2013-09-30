///
/// \file     rule_string.hpp
/// \brief    rules to read a string
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  rules to read a string

#ifndef LAURENA_RULE_STRING_H
#define LAURENA_RULE_STRING_H

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
/*              class rule_string                                               */ 
/*                                                                              */ 
/********************************************************************************/ 

template
<
	typename STRING=std::basic_string<char>, // returned string type
	typename CONTEXT=rule_context<>			 // context
>

class rule_string : public rule_templated<STRING, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_string() : rule_templated<STRING, CONTEXT>() 
	{ }
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file