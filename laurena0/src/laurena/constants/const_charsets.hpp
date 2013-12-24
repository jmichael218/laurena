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
	static const charset<CHARTYPE> VARNAME;		//abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_
	static const charset<CHARTYPE> IDNAME;		//  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/"
	static const charset<CHARTYPE> FULLPATH_FILENAME_SEPARATOR; // "/\\:" ;
	static const charset<CHARTYPE> LOWCASE;		// "abcdefghijklmnopqrstuvwxyz" ;
	static const charset<CHARTYPE> HEXADECIMAL; // "0123456789abcdefABCDEF";
	static const charset<CHARTYPE> TABS;		// \r\n\r and space
	static const charset<CHARTYPE> TABS_NO_EOL; // // \r\t space, no eol
	static const charset<CHARTYPE> LETTERS;     // "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	static const charset<CHARTYPE> BINARY;
	static const charset<CHARTYPE> ACCENTS;
	static const charset<CHARTYPE> URI;
	static const charset<CHARTYPE> VARLIST;		// "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t "
};

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::RN ( sliteral<CHARTYPE>("\r\n"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::NUMBERS ( sliteral<CHARTYPE>("0123456789"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::VARNAME (sliteral<CHARTYPE> ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::IDNAME (sliteral<CHARTYPE> ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::FULLPATH_FILENAME_SEPARATOR (sliteral<CHARTYPE> ("/\\:"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::LOWCASE (sliteral<CHARTYPE> ("abcdefghijklmnopqrstuvwxyz"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::HEXADECIMAL (sliteral<CHARTYPE> ("0123456789abcdefABCDEF"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::TABS (sliteral<CHARTYPE> ("\r\n\t "));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::TABS_NO_EOL (sliteral<CHARTYPE> ("\r\t "));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::LETTERS (sliteral<CHARTYPE> ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::BINARY (sliteral<CHARTYPE> ("01"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::ACCENTS (sliteral<CHARTYPE> ("יטךכאגהןמüûצפח"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::URI (sliteral<CHARTYPE> ("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-/?=&%"));

template<typename CHARTYPE>
const charset<CHARTYPE> const_charsets<CHARTYPE>::VARLIST (sliteral<CHARTYPE> ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n\t "));

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif