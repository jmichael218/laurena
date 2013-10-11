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

#include <string>

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
	typedef const std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >&	const_ref_mystring;

	typedef CHARTYPE*																			ptr_chartype;
	typedef const CHARTYPE*																		const_ptr_chartype;
	typedef const CHARTYPE&																		const_ref_chartype;

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	source_location() : 
		
		_filename(), _function(), _column(0), _line(0)
		{ }

	source_location(const std::string& filename) 
		
		: _filename(filename), _column(0), _line(0) 
	    { }

	source_location(const std::string& filename, const std::string& function, unsigned long int line =0) 
		
		: _filename(filename), _function(function), _column(0), _line(line) 
	    { }	

	source_location(const char* filename, const char* function=nullptr) 
		
		: _filename(filename), _function(function), _column(0), _line(0) 
	    { }

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
	inline
	void count(ITERATOR first, ITERATOR last)
	{
		while (first != last)
			this->count(*first++);		
	}

	/****************************************************************************/
	/*			setters															*/ 
	/****************************************************************************/ 

	inline void filename(const std::string& path) { this->_filename = path; }
	inline void function(const std::string& name) {this->_function = name;  }

	/****************************************************************************/
	/*			getters															*/ 
	/****************************************************************************/ 

	inline const std::string&				filename() const					   { return this->_filename; }
	inline const std::string&				function() const					   { return this->_function; }
	inline unsigned long int		column  () const                       { return _column ; }
	inline unsigned long int		line    () const                       { return _line ; }

	/****************************************************************************/ 
	/*          other functions                                                 */ 
	/****************************************************************************/ 

	void reset()
	{
		this-> _filename = this->_function = "" ;
		this->_column = _line = 0;
	}
	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:

	std::string			_filename;
	std::string			_function;
	unsigned long int   _column;
	unsigned long int   _line;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
