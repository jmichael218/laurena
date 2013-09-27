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

#include <memory>

#include <laurena/types/source_location.hpp>
#include <laurena/traits/in_traits.hpp>
#include <laurena/types/charset.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule                                                      */ 
/*                                                                              */ 
/********************************************************************************/ 
class rule_const 
{
	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 	
	public:

	static const unsigned long int SYNTAX_ERROR;
};
const unsigned long int rule_const::SYNTAX_ERROR = (unsigned long int) -1;




template<typename OBJECT=int, typename SOURCE_TRAITS = in_traits<const char*>, typename SOURCE_LOCATION = source_location<char, '\n'>>
class rule_context
{
public:

	typedef typename SOURCE_TRAITS::chartype		chartype;
	typedef typename SOURCE_TRAITS					traits;
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
class rule_basic
{
public:

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const =0;
};



template<typename T, typename CONTEXT = rule_context<>>
class rule_template : public rule_basic<CONTEXT>
{
public:

	typedef std::function<void (const T&, typename CONTEXT::object)> callback_read_type;

	rule_template () : rule_basic<CONTEXT>(), _read_cb(nullptr) {};

	/*******************************************************************************/ 
	/*		operators															   */ 
	/*******************************************************************************/ 

	rule_template<T, CONTEXT>& operator [] (callback_read_type cb)
	{
		return cbread(cb);
	}

	/*******************************************************************************/
	/*		setters																   */ 
	/*******************************************************************************/ 

	inline
	rule_template<T, CONTEXT>& cbread(callback_read_type cb) 
	{ this->_read_cb = cb; return *this; }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		return rule_const::SYNTAX_ERROR;
	}

	/*******************************************************************************/ 
	/*		protected:															   */ 
	/*******************************************************************************/ 
	protected:

	inline void readed(const T& t, CONTEXT& context) const
	{
		if (_read_cb) 
			_read_cb (t, context._object);
	}

	callback_read_type		_read_cb;

};

template<typename CONTEXT = rule_context<>>
class rule_ptr : public std::shared_ptr<rule_basic<CONTEXT>> 
{
public:

	rule_ptr(rule_basic<CONTEXT>* ptr) : std::shared_ptr<rule_basic<CONTEXT>>(ptr) 
	{ }

};

template<typename T, typename CONTEXT=rule_context<>>
class rule_ptr_template : public rule_ptr<CONTEXT>
{
public:

	rule_ptr_template(rule_template<T,CONTEXT>* ptr) : rule_ptr(ptr)
	{ }

	rule_ptr_template<T, CONTEXT>& operator [] ( typename rule_template<T,CONTEXT>::callback_read_type cb)
	{
		rule_template<T,CONTEXT>*p = (rule_template<T,CONTEXT>*) this->get();
		p->operator[] (cb);
		return *this;
	}
};

template<typename CONTEXT>
class rule_table : public std::vector<rule_ptr<CONTEXT>>
{
public:

	rule_table () { };
	rule_table (rule_table&& r) : std::vector<std::unique_ptr<rule_basic<CONTEXT>>> (r)
	{ }


	unsigned long int read(CONTEXT& context) const
	{
		unsigned long int res = 0, r2;
		for (const rule_ptr<CONTEXT>& r : *this)
		{
			r2 = r->read(context);

			if (r2 == 0 || r2 == rule_const::SYNTAX_ERROR)
				return rule_const::SYNTAX_ERROR;

			context._first = CONTEXT::traits::readed(context._first, r2);
			res += r2;
		}
		return res;
	}
};



template<typename CHARTYPE =char, typename CONTEXT = rule_context<>>
class rule_static_char : public rule_template<CHARTYPE, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_static_char(CHARTYPE charExpected) : rule_template<CHARTYPE, CONTEXT>(), _value(charExpected)
	{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		if (*context._first == this->_value)
		{			
			context._location.count(*context._first);
			this->readed(this->_value,context);
			return 1;
		}
		return rule_const::SYNTAX_ERROR;
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	CHARTYPE _value;

};

template<typename STRING=std::basic_string<char>, typename CONTEXT=rule_context<>>
class rule_string : public rule_template<STRING, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_string() : rule_template<STRING, CONTEXT>() 
	{ }
};

template<typename STRING=std::basic_string<char>, typename CHARSET=charset<char>, typename CONTEXT=rule_context<>>
class rule_charset : public rule_string<STRING, CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors, destructor										*/ 
	/****************************************************************************/ 
	rule_charset(const CHARSET& cset) : rule_string<STRING, CONTEXT>(), _charset(cset)
	{ }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 
	virtual unsigned long int read (CONTEXT& context) const
	{
		STRING ss = std::move(readwhile<CONTEXT::iterator, CHARSET, STRING>(context._first, context._last,this->_charset));
		if (ss.length() == 0)
			return rule_const::SYNTAX_ERROR;
		else
		{
			context._location.count(ss);
			this->readed(ss,context);
			return ss.length();
		}
	}

	/****************************************************************************/ 
	/*          protected datas                                                 */ 
	/****************************************************************************/ 
	protected:
	const CHARSET& _charset;

};

template<typename CONTEXT= rule_context<>>
class rule
{
public:

	static rule_ptr_template<typename CONTEXT::chartype, CONTEXT> char_(typename CONTEXT::chartype value)
	{
		return rule_ptr_template<typename CONTEXT::chartype, CONTEXT>(new rule_static_char<typename CONTEXT::chartype, CONTEXT>(value));
	}

	static rule_ptr_template<std::basic_string<typename CONTEXT::chartype>, CONTEXT> set_(const charset<typename CONTEXT::chartype>& cset)
	{
		auto p = new rule_charset<std::basic_string<typename CONTEXT::chartype>, charset<typename CONTEXT::chartype>>(cset);
		return rule_ptr_template<std::basic_string<typename CONTEXT::chartype>, CONTEXT> (p);
	}
};

template<typename CONTEXT=rule_context<>>
class rules
{
public:

	rules<CONTEXT>& operator<<(rule_ptr<CONTEXT>& r)
	{
		_rules.push_back(r);
		return *this;
	}

	template<typename T>
	rules<CONTEXT>& operator<<(rule_template<T, CONTEXT>* r)
	{
		_rules.push_back(rule_ptr<CONTEXT>(r));
		return *this;
	}


	inline
	rules<CONTEXT>& operator << (typename CONTEXT::chartype value)
	{
		return *this << rule<CONTEXT>::char_(value);
	}

	inline 
	rules<CONTEXT>& operator << (const charset<typename CONTEXT::chartype>& cset )
	{
		return *this << rule<CONTEXT>::set_(cset);
	}


	template<typename T>
	rules<CONTEXT>& operator<< (std::function<void (const T&, typename CONTEXT::object)> cb)
	{
		rule_template<T, CONTEXT>* r = dynamic_cast<rule_template<T, CONTEXT>*>(this->_rules.back().get());
		r->cbread(cb);
		return *this;
	}

	inline 
	unsigned long int read (CONTEXT& context)
	{ return this->_rules.read(context); }

protected:
	rule_table<CONTEXT>		_rules;
} ;



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