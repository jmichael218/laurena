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
#include <laurena/traits/string_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              implementation of symbols per keys                              */ 
/*                                                                              */ 
/********************************************************************************/ 

// empty implementation for failed substitution
template
<
	  bool ENABLED_CHARTYPE
	, bool ENABLED_STRINGTYPE

	, typename KEY							// key type of the symbols
	, typename VALUE							// value type of the symbols
>
struct symbols_implementation
{
};

// implementation when KEY is a chartype
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
>
struct symbols_implementation<true, false, KEY, VALUE>
{
	static inline
	bool is_prefix (const KEY& sprefix, const KEY& key)
	{ return sprefix == key; }		 	
};

// implementation when KEY is a std::basic_string<chartype> class
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
>
struct symbols_implementation<false, true, KEY, VALUE>
{
	typedef typename in_traits<KEY>::iterator		iterator;
	typedef in_traits<KEY>							traits;
	
	static inline
	bool is_prefix (const KEY& sprefix,  const KEY& key )
	{


		return prefix<iterator>(traits::begin(key), traits::begin(sprefix), traits::end(sprefix));
	}
};

// tag dispatcher for the implementation
template
<
	typename KEY							// key type of the symbols
	,typename VALUE							// value type of the symbols
>
struct symbols_implementation_displatch 

	: public symbols_implementation
	<
		std::is_integral<KEY>::value
		,string_traits<KEY>::is_string::value
		,KEY
		,VALUE
	>

	{ }
;

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
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef typename symbols<KEY, VALUE>::const_iterator tconst_iterator;

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
	tconst_iterator value(const VALUE& v) const
	{
		for (tconst_iterator it = this->cbegin(); it != this->cend(); it++)
			if (it->second == v)
				return it;
		return this->end();
	}

	// search key by value
	tconst_iterator key(const KEY& k) const
	{
		for (tconst_iterator it = this->cbegin(); it != this->cend(); it++)
			if (it->first == k)
				return it;
		return this->end();
	}

	unsigned long int candidates(const KEY& prefix) const
	{
		unsigned long int res = 0;
		for (const std::pair<KEY, VALUE>& p : *this)
			res  += symbols_implementation_displatch<KEY, VALUE>::is_prefix(prefix, p.first) ? 1 : 0 ;

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
