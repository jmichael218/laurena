///
/// \file     symbols.hpp
/// \brief    A symbol array class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   A symbol array class
///

#ifndef LAURENA_SYMBOLS_H
#define LAURENA_SYMBOLS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/traits/string_traits.hpp>
#include <laurena/algorithm/strings/prefix.hpp>
#include <laurena/traits/in_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              implementation of symbols per keys                              */ 
/*                                                                              */ 
/********************************************************************************/ 

class symbols_implementation
{

	template <typename KEY>	
	inline
	static bool is_prefix
	(
	
		const KEY& sprefix, 
		const KEY& key,

		typename std::enable_if<std::is_integral<KEY>::value>::type = true
	
	)
	{
		return sprefix == key;
	}

	template <typename KEY>
	inline
	static bool is_prefix
	(

		const KEY& sprefix, 
		const KEY& key,

		typename std::enable_if<string_traits<KEY>::is_string>::type = true
	)
	{
		typedef typename in_traits<KEY>::iterator		iterator;
		typedef in_traits<KEY>							traits;

		return prefix<iterator>(traits::first(key), traits::first(sprefix), traits::last(sprefix));
	}
};

/********************************************************************************/ 
/*                                                                              */ 
/*              class symbols                                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
template<typename KEY, typename VALUE>
class symbols : public std::vector<std::pair<KEY, VALUE>>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 

	// defaut constructor
	symbols () : std::vector<std::pair<KEY, VALUE>> () 
	{ }

	// constructor with initializer_list
	// symbols<char,bool> ( { values } );
	template<size_t N>
	symbols (const std::pair<KEY, VALUE> (&ref_array) [N]) : std::vector<std::pair<KEY, VALUE>> (&ref_array[0], &ref_array[N])
	{ }

	/****************************************************************************/ 
	/*			search functions												*/ 
	/****************************************************************************/ 
	// search value by key
	typename symbols<KEY, VALUE>::const_iterator value(const VALUE& v) const
	{
		for (const_iterator it = this->begin(); it != this->end(); it++)
			if (it->second == v)
				return it;
		return this->end();
	}

	// search key by value
	typename symbols<KEY, VALUE>::const_iterator key(const KEY& k) const
	{
		for (const_iterator it = this->begin(); it != this->end(); it++)
			if (it->first == k)
				return it;
		return this->end();
	}

	unsigned long int candidates(const KEY& prefix) const
	{
		unsigned long int res = 0;
		for (const std::pair<KEY, VALUE>& p : *this)
			res  += symbols_implementation<KEY>::is_prefix(prefix, p.first) ? 1 : 0 ;

		return res;
	}

	/****************************************************************************/ 
	/*			other functions													*/ 
	/****************************************************************************/ 
	void  regexp(std::ostream& out)    const
	{
		bool first = true;
		out << '(';
		for (const std::pair<KEY, VALUE>& p : *this)
		{
			if (first)
				first = false;
			else
				out << '|';

			out << p.first;
		}
		out << ')';
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
