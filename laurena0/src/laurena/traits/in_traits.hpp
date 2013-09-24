///
/// \file     in_traits.hpp
/// \brief    Deduce from type various subtypes for use in generic parsing functions
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Deduce from type various subtypes for use in generic parsing functions
///

#ifndef LAURENA_IN_TRAITS_H
#define LAURENA_IN_TRAITS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <string>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          template of in_traits                                                */ 
/*********************************************************************************/ 

template<typename T>
struct in_traits
{

};

template<typename CHARTYPE>
struct in_traits<std::basic_istream<CHARTYPE>>
{
	typedef std::basic_istream<CHARTYPE>			type;
	typedef CHARTYPE								chartype;
	typedef std::istreambuf_iterator<CHARTYPE>		iterator;
	typedef std::basic_string<CHARTYPE>				string;

	inline
	static iterator first(type& stream) 
	{ return iterator(stream); }

	inline
	static iterator last(type& stream) 
	{ return iterator(); }
};

template<typename CHARTYPE>
struct in_traits<std::basic_string<CHARTYPE>>
{
	typedef const std::basic_string<CHARTYPE>						type;
	typedef CHARTYPE												chartype;
	typedef const CHARTYPE*											iterator;
	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<char>>	string;

	inline
	static iterator first(const type& str)
	{ return str.data(); }

	inline
	static iterator last(const type& str)
	{ return str.data() + str.length(); }
};

template<typename CHARTYPE>
struct in_traits<const CHARTYPE*>
{
	typedef const CHARTYPE*							type;
	typedef CHARTYPE								chartype;
	typedef const CHARTYPE*							iterator;
	typedef std::basic_string<CHARTYPE>				string;

	inline
	static iterator first(type str)
	{ return str; }

	inline
	static iterator last(type str)
	{ return str + std::char_traits<CHARTYPE>::length(str); }
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
