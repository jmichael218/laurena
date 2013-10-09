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
	typedef T												type;
	typedef typename T::char_type							chartype;
	typedef std::istream_iterator<typename T::char_type>	iterator;
	typedef std::basic_string<typename T::char_type>		string;

	inline
	static iterator first(type& stream) 
	{ return iterator(stream); }

	inline
	static iterator last(type& stream) 
	{ return iterator(); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it }
};

template<typename T>
struct in_traits<const T> : in_traits<T> {};

template<typename T>
struct in_traits<const T&> : in_traits<T> {};

template<class CHARTYPE, size_t N>
struct in_traits<const CHARTYPE[N]>
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
	{ return str + N; }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }
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

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }
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

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }
};

template<class CHARTYPE, size_t N>
struct in_traits<CHARTYPE[N]>
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

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }
};

template<class CHARTYPE>
struct in_traits<CHARTYPE[]>
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

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }
};



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
