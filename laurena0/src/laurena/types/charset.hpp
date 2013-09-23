///
/// \file     charset.hpp
/// \brief    A class to wrap a given alphabet and give operations of validations / parsing
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A class to wrap a given alphabet and give operations of validations / parsing
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
#include <laurena/algorithm/strings/alphabet.hpp>

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
	typedef std::basic_string<CHARTYPE>					string;
	typedef typename string::iterator					iterator;

	/****************************************************************************/ 
	/*			constructor, destructors										*/ 
	/****************************************************************************/ 

	charset () : _characters () 
	{ }

	charset (typename const CHARTYPE* characters) : _characters (std::move(alphabet(characters)))
	{ }

	charset (typename const string& characters) : _characters (std::move(alphabet(characters)))
	{ }

	/****************************************************************************/ 
	/*			getters															*/ 
	/****************************************************************************/ 

	inline string& characters () const  
	{ return _characters ; }


	inline bool test(CHARTYPE c) const
	{ return this->_characters.find(c) !=  string::npos; } 

	bool validate(typename iterator& first, typename const iterator& last) const
	{
		while (first != last)
		{
			if (this->_characters.find(*first++) == string::npos)
				return false;
		}
		return true;
	}

	bool validate(const CHARTYPE* first, const CHARTYPE* last) const
	{
		while (first != last)
		{
			if (this->_characters.find(*first++) == string::npos)
				return false;
		}
		return true;
	}

	inline
	bool validate (const CHARTYPE* pstr, size_t size)
	{
		return this->validate(pstr, pstr+size);
	}

	inline
	bool validate (const CHARTYPE* pstr)
	{
		return this->validate(pstr, pstr + std::char_traits<CHARTYPE>::length(pstr) );
	}

	inline
	bool validate (const string& str)
	{
		return this->validate(str.data(), str.data() + str.length() );
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	string		_characters;

};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif