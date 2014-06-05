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
#include <iterator>     // std::istream_iterator

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
	static iterator begin(type& stream) 
	{ return iterator(stream); }

	inline
	static iterator end(type& stream) 
	{ return iterator(); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it; }

	inline
	static iterator back(type& stream, iterator current, chartype c)
	{ 
		stream.putback(c);
		return current;
	}

	inline
	static iterator back(type& stream, iterator current, const string& s)
	{
		for (chartype c : s)
			stream.putback(c);
		return current;		
	}
	
	inline
	static size_t length(type& stream)
	{ return std::distance(begin(stream), end(stream)); }
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
	static iterator begin(type str)
	{ return str; }

	inline
	static iterator end(type str)
	{ return str + N-1; } // -1 because last is a zero 

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& carray, iterator current, chartype c)
	{ 
		--current;
		return current;
	}

	inline
	static iterator back(type& stream, iterator current, const string& s)
	{
		current -= s.size();
		return current;		
	}
	
	inline
	static size_t length(type& carray)
	{ return N; }
};

template<typename CHARTYPE>
struct in_traits<std::basic_string<CHARTYPE>>
{
	typedef std::basic_string<CHARTYPE>						        type;
	typedef CHARTYPE												chartype;
	typedef typename std::basic_string<CHARTYPE>::iterator			iterator;
	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<char>>	string;

	inline
	static iterator begin(type& str)
	{ return str.begin(); }

	inline
	static iterator end(type& str)
	{ return str.end(); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& str, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
	
	inline
	static size_t length(type& str)
	{ return str.length(); }
};

template<typename CHARTYPE>
struct in_traits<const std::basic_string<CHARTYPE>>
{
	typedef const std::basic_string<CHARTYPE>						        type;
	typedef CHARTYPE												        chartype;
	typedef typename std::basic_string<CHARTYPE>::const_iterator			iterator;
	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<char>>	string;

	inline
	static iterator begin(type& str)
	{ return str.cbegin(); }

	inline
	static iterator end(type& str)
	{ return str.cend(); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& str, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
	
	inline
	static size_t length(type& str)
	{ return str.length(); }
};

template<typename CHARTYPE>
struct in_traits<const CHARTYPE*>
{
	typedef const CHARTYPE*							type;
	typedef CHARTYPE								chartype;
	typedef const CHARTYPE*							iterator;
	typedef std::basic_string<CHARTYPE>				string;

	inline
	static iterator begin(type str)
	{ return str; }

	inline
	static iterator end(type str)
	{ return str + std::char_traits<CHARTYPE>::length(str); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& carray, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
	
	inline
	static size_t length(type str)
	{
	    return str ? strlen(str) : 0;
	}
};

template<class CHARTYPE, size_t N>
struct in_traits<CHARTYPE[N]>
{
	typedef const CHARTYPE*							type;
	typedef CHARTYPE								chartype;
	typedef const CHARTYPE*							iterator;
	typedef std::basic_string<CHARTYPE>				string;

	inline
	static iterator begin(type str)
	{ return str; }

	inline
	static iterator end(type str)
	{ return str + std::char_traits<CHARTYPE>::length(str); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& carray, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
	
	inline
	static size_t length(type str)
	{ return N; }
};

template<class CHARTYPE>
struct in_traits<CHARTYPE[]>
{
	typedef const CHARTYPE*							type;
	typedef CHARTYPE								chartype;
	typedef const CHARTYPE*							iterator;
	typedef std::basic_string<CHARTYPE>				string;

	inline
	static iterator begin(type str)
	{ return str; }

	inline
	static iterator end(type str)
	{ return str + std::char_traits<CHARTYPE>::length(str); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& carray, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
	
	inline
	static size_t length(type str)
	{ return std::char_traits<CHARTYPE>::length(str); }
};



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
