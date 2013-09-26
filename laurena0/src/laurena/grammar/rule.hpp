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

#include <laurena/types/source_location.hpp>
#include <laurena/traits/in_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule                                                      */ 
/*                                                                              */ 
/********************************************************************************/ 

template<typename OBJECT=int, typename SOURCE_TRAITS = in_traits<const char*>, typename SOURCE_LOCATION = source_location<char, '\n'>>
class rule_context
{
public:

	typedef typename SOURCE_TRAITS::iterator		iterator;
	typedef typename SOURCE_LOCATION				location;
	typedef typename OBJECT							object;

	rule_context(iterator first, iterator last) : _first(first), _last(last) { };

	iterator			_first;
	iterator			_last;
	location			_location;
	object				_object;

};


template<typename CONTEXT = rule_context<>>
class rule
{
	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 	
	public:

	static const unsigned long int ERROR_SYNTAX;

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const =0;
};

template<typename CONTEXT>
const unsigned long int rule<CONTEXT>::ERROR_SYNTAX = (unsigned long int) -1;

template<typename T, typename CONTEXT = rule_context<>>
class rule_template : public rule<CONTEXT>
{
public:

	typedef std::function<void (const T&, typename CONTEXT::object)> callback_type;

	rule_template () : rule<CONTEXT>(), _cb(nullptr) {};

	rule_template (callback_type callback_function) : rule<CONTEXT> (), _cb(callback_function) {};

	/*******************************************************************************/ 
	/*		protected:															   */ 
	/*******************************************************************************/ 
	protected:

	inline void callback(const T& t, CONTEXT& context) const
	{
		if (_cb) 
			_cb (t, context._object);
	}

	callback_type		_cb;

};


template<typename CHARTYPE =char, typename CONTEXT = rule_context<>>
class rule_static_char : public rule_template<CHARTYPE, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_static_char(CHARTYPE charExpected, callback_type callback=nullptr) : rule_template<CHARTYPE, CONTEXT>(callback), _value(charExpected)
	{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		if (*context._first == this->_value)
		{			
			context._location.count(*context._first++);
			this->callback(this->_value,context);
			return 1;
		}
		return rule<CONTEXT>::ERROR_SYNTAX;
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