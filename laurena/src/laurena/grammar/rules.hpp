///
/// \file     rules.hpp
/// \brief    grammar rules
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   grammar rules
///

#ifndef LAURENA_RULES_H
#define LAURENA_RULES_H

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

#include <laurena/source/source_location.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule                                                      */ 
/*                                                                              */ 
/********************************************************************************/ 

template<typename CHARTYPE = char, CHARTYPE EOL='\n'>
class rule
{
	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 
	public:
	typedef std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >				mystring;
	typedef const std::basic_string<CHARTYPE, std::char_traits<CHARTYPE>, std::allocator<CHARTYPE> >&		const_ref_mystring;
	typedef typename mystring::iterator																		iterator;
	typedef typename mystring::iterator&																	ref_iterator;

	typedef CHARTYPE*																						ptr_chartype;
	typedef const CHARTYPE*																					const_ptr_chartype;
	typedef const CHARTYPE&																					const_ref_chartype;

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual bool read (ref_iterator first, iterator last, source_location<CHARTYPE, EOL>& location, any& value) const =0;
};

template<typename CHARTYPE = char, CHARTYPE EOL='\n'>
class rule_static_char : public rule<CHARTYPE, EOL>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_static_char(CHARTYPE charExpected) : _value(charExpected)
	{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual bool read (ref_iterator first, iterator last, source_location<CHARTYPE, EOL>& location, any& value) const
	{
		if (*first == _value)
		{			
			location.count(*first);
			value = _value;
			first++;
			return true;
		}
		return false;
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	CHARTYPE _value;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif