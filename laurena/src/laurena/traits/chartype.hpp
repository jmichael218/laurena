///
/// \file     chartype.hpp
/// \brief    traits for characters types
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   traits for characters types
///

#ifndef LAURENA_CHARTYPE_H
#define LAURENA_CHARTYPE_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              character type traits                                           */ 
/*                                                                              */ 
/********************************************************************************/ 

template<typename CHARTYPE>
class chartype
{

public:

	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >				mystring;
	typedef const std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >&		const_ref_mystring;
	typedef typename mystring::iterator																		iterator;
	typedef typename mystring::iterator&																	ref_iterator;

	typedef CHARTYPE*																						ptr_chartype;
	typedef const CHARTYPE*																					const_ptr_chartype;
	typedef const CHARTYPE&																					const_ref_chartype;


};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif