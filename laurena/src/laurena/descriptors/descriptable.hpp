/// \file     descriptable.hpp
/// \brief    A base class for descriptable types (class, field members, functions, methods)
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A base class for descriptable types (class, field members, functions, methods)
///

#ifndef LAURENA_DESCRIPTABLE_H
#define LAURENA_DESCRIPTABLE_H

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

#include <laurena/descriptors/annotation.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

class descriptable 
{
	public:

	/****************************************************************************/ 
	/*																			*/ 
	/*			CONSTRUCTOR / DESTRUCTOR										*/ 
	/*																			*/ 
	/****************************************************************************/ 
    //! Constructor    
    /*! This is the only constructor available. Name and type can't be changed over the descriptable lifetime.    
        \param name The identifier name of the class. It must be unique.
    */ 
	descriptable (const char* name);

    //! Destructor
    /*! This is the class destructor. */
	virtual ~descriptable ();

	/****************************************************************************/ 
	/*																			*/ 
	/*			ANNOTATIONS														*/ 
	/*																			*/ 
	/****************************************************************************/ 
	//! Returns a reference to the annotations map
	inline const annotations_map& annotations () const
	{ return this->_annotations; }

	//! Add an annotation
	descriptable& annotate(annotation* ptrvalue);

	/****************************************************************************/ 
	/*																			*/ 
	/*			GETTERS / SETTERS												*/ 
	/*																			*/ 
	/****************************************************************************/ 
	inline const std::string& name () const
	{
		return this->_name ; 
	}

	/****************************************************************************/ 
	/*																			*/ 
	/*			PROTECTED FIELDS												*/ 
	/*																			*/ 
	/****************************************************************************/ 
	protected:
	std::string			_name;
	annotations_map		_annotations;

};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif