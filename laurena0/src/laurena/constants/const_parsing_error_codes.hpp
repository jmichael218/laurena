///
/// \file     const_parsing_error_codes.hpp
/// \brief    error codes returned by the read parsing function of rules objects
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   error codes returned by the read parsing function of rules objects
///

#ifndef LAURENA_PARSING_ERROR_CODES_H
#define LAURENA_PARSING_ERROR_CODES_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/types/source_location.hpp>
#include <laurena/traits/in_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

	/********************************************************************************/ 
	/*                                                                              */ 
	/*              class rule                                                      */ 
	/*                                                                              */ 
	/********************************************************************************/ 
	class pec // abbrev of parsing error codes
	{
		/****************************************************************************/ 
		/*			typedefs														*/ 
		/****************************************************************************/ 	
	public:

		static const unsigned long int SYNTAX_ERROR;
	};
	const unsigned long int pec::SYNTAX_ERROR = (unsigned long int) -1;

	/********************************************************************************/ 
	/*          bottom file block                                                   */ 
	/********************************************************************************/ 

}
#endif
//End of file

