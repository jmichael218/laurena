///
/// \file     rule_ptr.hpp
/// \brief    shared ptr rule wrapper
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   shared ptr rule wrapper
///

#ifndef LAURENA_RULE_PTR_H
#define LAURENA_RULE_PTR_H

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
#include <laurena/grammar/rule_basic.hpp>
#include <laurena/grammar/rule_or.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_ptr                                                  */ 
/*                                                                              */ 
/********************************************************************************/ 

// This is the class wrapping a smart rule_basic  pointer
template 
<
	typename CONTEXT
>

class rule_ptr : public std::shared_ptr<rule_basic<CONTEXT>> 
{
public:

	/************************************************************************/ 
	/*		constructor														*/ 
	/************************************************************************/ 
	rule_ptr(rule_basic<CONTEXT>* ptr) 
		
		: std::shared_ptr<rule_basic<CONTEXT>>(ptr) 
		{ }

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file
