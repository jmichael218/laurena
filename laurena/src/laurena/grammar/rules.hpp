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

#include <laurena/traits/chartype.hpp>

#include <laurena/source/source_location.hpp>
#include <laurena/toolboxes/cstring.hpp>

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
	typedef chartype<CHARTYPE> c;



	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual bool read (typename c::iterator& first, typename c::iterator last, source_location<CHARTYPE, EOL>& location, any& value) const =0;
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
	virtual bool read (typename c::iterator& first, typename c::iterator last, source_location<CHARTYPE, EOL>& location, any& value) const
	{
		if (*first == _value)
		{			
			location.count(*first);
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

#ifdef BOBJOE
template<typename CHARTYPE = char, CHARTYPE EOL='\n'>
class rule_integer_field : public rule<CHARTYPE, EOL>
{
public:



	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_integer_field(const field& f) : _field(f)
	{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual bool read (ref_iterator first, iterator last, source_location<CHARTYPE, EOL>& location, any& value) const
	{
		std::string v ;
		word32 readed = cstring::readInteger(tokenizer._ptr,v);
		if (readed)
		{			
			location.count(*first);
			first++;
			return true;
		}
		return false;
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	const field&			_field;

};
#endif

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif