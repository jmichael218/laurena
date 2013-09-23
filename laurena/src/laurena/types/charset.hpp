///
/// \file     charset.hpp
/// \brief    A dynamic_bitset boost set of bits enhanced to hold mask for character sets
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A dynamic_bitset boost set of bits enhanced to hold mask for character sets
///

#ifndef LAURENA_CHARSET_H
#define LAURENA_CHARSET_H

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

#include <laurena/traits/chartype.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          CharSet                                                              */ 
/*********************************************************************************/ 

template<typename CHARTYPE=char>
class charset
{
public:

	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 	
	typedef chartype<CHARTYPE> c;

	/*******************************************************************************/ 
	/*			constructor, destructors										   */ 
	/*******************************************************************************/ 

	charset () : _characters () 
	{ }
	charset (typename const CHARTYPE* characters) : _characters (characters)
	{ }

	charset (typename const c::mystring& characters) : _characters (characters)
	{ }

	/****************************************************************************/ 
	/*			getters															*/ 
	/****************************************************************************/ 

	inline typename const c::mystring& characters () const  
	{ return _characters ; }


	inline bool test(CHARTYPE c) const
	{ return this->_characters.find(c) !=  c::mystring::npos; } 


	bool validate(typename c::iterator& first, typename c::iterator last) const
	{
		while (first != last)
		{
			if (!this->_characters.find(*first++) == c::mystring::npos)
				return false;
		}
		return true;
	}

	bool validate(typename c::const_ptr_chartype first, typename c::const_ptr_chartype last) const
	{
		while (first != last)
		{
			if (!this->_characters.find(*first++) == c::mystring::npos)
				return false;
		}
		return true;
	}

	bool validate (typename const CHARTYPE* pstr, word32 size)
	{
		return this->validate(pstr, pstr+size);
	}

	bool validate (typename const CHARTYPE* pstr)
	{
		word32 sz =std::char_traits<CHARTYPE>::length(pstr);
		return this->validate(pstr, pstr+sz);
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	typename c::mystring		_characters;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif