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
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class symbols                                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
template<typename KEY, typename VALUE>
class symbols : public std::vector<std::pair<KEY, VALUE>>
{
public:

	symbols () : std::vector<std::pair<KEY, VALUE>> () 
	{ }

	template<size_t N>
	symbols (const std::pair<KEY, VALUE> (&ref_array) [N]) : std::vector<std::pair<KEY, VALUE>> (&ref_array[0], &ref_array[N])
	{ }

	typename symbols<KEY, VALUE>::const_iterator value(const VALUE& v) const
	{
		for (const_iterator it = this->begin(); it != this->end(); it++)
			if (it->second == v)
				return it;
		return this->end();
	}

	typename symbols<KEY, VALUE>::const_iterator key(const KEY& k) const
	{
		for (const_iterator it = this->begin(); it != this->end(); it++)
			if (it->first == k)
				return it;
		return this->end();
	}
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif