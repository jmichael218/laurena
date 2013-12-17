///
/// \file     parsing_context.hpp
/// \brief    context used when a rule is parsing a source
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   context used when a rule is parsing a source
///

#ifndef LAURENA_PARSING_CONTEXT_H
#define LAURENA_PARSING_CONTEXT_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class parsing_context                                           */ 
/*                                                                              */ 
/********************************************************************************/ 

template 
<	
	typename OBJECT=int,									//! Object to fill data
	typename SOURCE_TRAITS = in_traits<const char*>,		//! Traits of the source (file, string, stream ... )
	typename SOURCE_LOCATION = source_location<char, '\n'>, //! Object type that track file advancement
	typename OUTPUT = std::ostream							//! output 
>

class parsing_context
{
public:

	/************************************************************************/ 
	/*		typedefs														*/ 
	/************************************************************************/ 

	typedef typename SOURCE_TRAITS::chartype		chartype;		// the source character ( char for a string, wchar_t for a 16bits file, etc ... )
	typedef			 SOURCE_TRAITS					traits;			// source traits
	typedef typename SOURCE_TRAITS::iterator		iterator;		// iterator type (const char* for memory string, stream_iterator otherwhile
	typedef			 SOURCE_LOCATION				location;		// object type that track file advancement
	typedef			 OBJECT							object;			// object target
	typedef			 OUTPUT							output;			// output

	/************************************************************************/ 
	/*		constructor														*/ 
	/************************************************************************/ 

	// construction is initialisation
	parsing_context(iterator first, iterator last) : _first(first), _last(last), _output(nullptr) { };

	/************************************************************************/ 
	/*		functions														*/ 
	/************************************************************************/ 

	template <typename T>
	inline void count(T value)
	{
		if (this->_output)
			*this->_output << value;

		this->_location.count(value);
	}


	/************************************************************************/ 
	/*		parsing context													*/ 
	/************************************************************************/ 
	iterator			_first;										//! Current pointer to the source text
	iterator			_last;										//! End of the source text
	location			_location;									//! Location of the current pointer (filename, function, line, column)
	object				_object;									//! target
	output*				_output;									//! output

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file

