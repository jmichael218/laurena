///
/// \file     rule_templated.hpp
/// \brief    basic rule that parse and instancing a template object
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   basic rule that parse and instancing a template object
///

#ifndef LAURENA_RULE_TEMPLATED_H
#define LAURENA_RULE_TEMPLATED_H

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
#include <ostream>

#include <laurena/grammar/rule_basic.hpp>
#include <laurena/constants/const_parsing_error_codes.hpp>


/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_templated                                            */ 
/*                                                                              */ 
/********************************************************************************/ 

// A type dependant rules : The rule parse a type T object
template 
<
	typename T,								// type of object parsed (char, int ... )
	typename CONTEXT = parsing_context<>	// 
>

class rule_templated : public rule_basic<CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			typedefs														*/ 
	/****************************************************************************/ 

	// type of callback function executed when 
	typedef std::function<void (const T&, typename CONTEXT::object)> callback_read_type;

	/****************************************************************************/ 
	/*			constructors													*/ 
	/****************************************************************************/ 

	rule_templated () : rule_basic<CONTEXT>(), _read_cb(nullptr) 
	
	{ };

	/*******************************************************************************/ 
	/*		operators															   */ 
	/*******************************************************************************/ 

	inline
	rule_templated<T, CONTEXT>& operator [] (callback_read_type cb)

	{ return callback_readed(cb); }

	/*******************************************************************************/
	/*		setters																   */ 
	/*******************************************************************************/ 

	inline
	rule_templated<T, CONTEXT>&	callback_readed(callback_read_type cb) 

	{ this->_read_cb = cb; return *this; }

	/****************************************************************************/ 
	/*			virtual functions												*/ 
	/****************************************************************************/ 

	// By default, it fails
	virtual unsigned long int read (CONTEXT& context) const

	{ return pec::SYNTAX_ERROR; }

	/*******************************************************************************/ 
	/*		new functions													   */ 
	/*******************************************************************************/ 

	// to be called before returning an OK resultat in read functions
	inline void readed(const T& t, CONTEXT& context) const
	{
		if (_read_cb) 
			_read_cb (t, context._object);
	}

	/*******************************************************************************/ 
	/*		protected datas														   */ 
	/*******************************************************************************/ 
	protected:

	callback_read_type		_read_cb;		// callback called before returning an OK Resultat in read functions.

};

/********************************************************************************/ 
/*                                                                              */ 
/*              class rule_ptr_templated                                        */ 
/*                                                                              */ 
/********************************************************************************/ 

// Derivation of rule_ptr for rule_templated types.
template
<
	typename T, 
	typename CONTEXT=rule_context<>
>

class rule_ptr_templated : public rule_ptr<CONTEXT>
{
public:

	/****************************************************************************/ 
	/*			constructors													*/ 
	/****************************************************************************/ 

	rule_ptr_templated(rule_templated<T,CONTEXT>* ptr) : rule_ptr(ptr)
	{ }

	/****************************************************************************/ 
	/*			operators														*/ 
	/****************************************************************************/ 

	rule_ptr_templated<T, CONTEXT>& operator [] ( typename rule_templated<T,CONTEXT>::callback_read_type cb)
	{
		((rule_templated<T,CONTEXT>*) this->get()) -> operator [] (cb) ;
		return *this;
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
//End of file

