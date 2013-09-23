///
/// \file     const_charset.hpp
/// \brief    Generation of charset constants needed here and there
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Generation of charset constants needed here and there
///

#ifndef LAURENA_CONST_CHARSET_H
#define LAURENA_CONST_CHARSET_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/types/charset.hpp>
#include <laurena/literals/string_literal.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          generation of const charsets                                         */ 
/*********************************************************************************/ 

template<typename CHARTYPE=char>
class const_charsets
{
	public:
	static const charset<CHARTYPE> RN;			// \r\n
	static const charset<CHARTYPE> NUMBERS;		// = "0123456789" 
};

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::RN ( sliteral<CHARTYPE>("\r\n"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::NUMBERS ( sliteral<CHARTYPE>("0123456789"));

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif