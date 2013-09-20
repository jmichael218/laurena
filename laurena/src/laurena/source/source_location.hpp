///
/// \file     source_location.hpp
/// \brief    A location in a source text ( filename, column, line )
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A location in a source text ( filename, column, line )
///

#ifndef LAURENA_SOURCE_LOCATION_H
#define LAURENA_SOURCE_LOCATION_H

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

/*********************************************************************************/
/*          source_location                                                      */ 
/*********************************************************************************/ 

template<typename CHARTYPE = char, CHARTYPE EOL='\n'>
class source_location
{
public:

	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 
	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >			mystring;
	typedef const std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >&		const_ref_mystring;

	typedef CHARTYPE*																			ptr_chartype;
	typedef const CHARTYPE*																		const_ptr_chartype;
	typedef const CHARTYPE&																		const_ref_chartype;

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	source_location(const_ref_mystring filename) : _filename(filename), _column(0), _line(0) {}
	source_location(const_ptr_chartype filename) : _filename(filename), _column(0), _line(0) {}

	/****************************************************************************/ 
	/*			processing														*/ 
	/****************************************************************************/ 
	inline void count(const_ref_chartype c)
	{
		if (c == EOL)
		{
			++ this->_line;
			this->_column = 0;
		}
		else
		{
			++ this->_column;
		}
	}

	void count(const_ptr_chartype pstr)
	{
		while (*pstr)
			this->count(*pstr++);	
	}

	void count(const_ref_mystring refstr)
	{
		for (const_ref_chartype c : refstr)
			this->count(c);	
	}

	template<typename ITERATOR>
	void count(ITERATOR first, ITERATOR last)
	{
		while (first != last)
			this->count(*first++);		
	}

	/****************************************************************************/
	/*			getters															*/ 
	/****************************************************************************/ 

	inline const_ref_mystring&		filename() const					   { return this->_filename; }
	inline word32					column  () const                       { return _column ; }
	inline word32					line    () const                       { return _line ; }

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	mystring		_filename;
	word32          _column;
	word32          _line;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
