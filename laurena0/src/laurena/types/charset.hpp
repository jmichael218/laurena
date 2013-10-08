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

/************************** std lib includes ************************************/
// for std::function
#include <functional>		

/************************** laurena0 lib includes *******************************/
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
	typedef std::function<bool (const CHARTYPE&)>		test_function;
	typedef typename CHARTYPE							chartype;

	/****************************************************************************/ 
	/*			constructor, destructors										*/ 
	/****************************************************************************/ 

	charset () 
		
		: _characters (), 
		, _condition_function([&] (const CHARTYPE& c) {return this->test(c);})

		{ }

	charset (const charset<CHARTYPE>& cset) 
		
		: _characters(cset._characters)
		, _condition_function([&] (const CHARTYPE& c) {return this->test(c);})

		{ }

	charset (typename const CHARTYPE* characters) 
		
		: _characters (std::move(alphabet(characters)))
		, _condition_function([&] (const CHARTYPE& c) {return this->test(c);})

		{ }

	charset (typename const string& characters) 
		
		: _characters (std::move(alphabet(characters)))
		, _condition_function([&] (const CHARTYPE& c) {return this->test(c);})

		{ }

	/****************************************************************************/ 
	/*			getters															*/ 
	/****************************************************************************/ 

	inline const string& characters () const  
	{ return _characters ; }


	inline bool test(CHARTYPE c) const
	{ return this->_characters.find(c) !=  string::npos; } 

	inline const test_function& condition() const
	{ return this->_condition_function; }
		 		
	/****************************************************************************/ 
	/*			string validation functions										*/ 
	/****************************************************************************/ 

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
	bool validate (const CHARTYPE* pstr, size_t size) const
	{
		return this->validate(pstr, pstr+size);
	}

	inline
	bool validate (const CHARTYPE* pstr) const
	{
		return this->validate(pstr, pstr + std::char_traits<CHARTYPE>::length(pstr) );
	}

	inline
	bool validate (const string& str) const
	{
		return this->validate(str.data(), str.data() + str.length() );
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	string			_characters;
	test_function	_condition_function;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif