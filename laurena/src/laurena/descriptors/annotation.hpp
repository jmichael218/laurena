/// \file     annotation.hpp
/// \brief    A base class for annotations
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A base class for annotations
///

#ifndef LAURENA_ANNOTATIONS_H
#define LAURENA_ANNOTATIONS_H

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

class descriptable;

class annotation
{



	/****************************************************************************/ 
	/*		constructor, destructor												*/ 
	/****************************************************************************/ 
	public:
	annotation (const std::string& name);
	annotation (const char* name);
	virtual ~annotation ();
		
	/****************************************************************************/ 
	/*		getters / setters													*/ 
	/****************************************************************************/ 

	/// \brief return name of the annotation
	/// This getter function return a const reference to the annotation name.
	/// \return const reference to the string name
	inline const std::string&	name ()		const		{ return this->_name ; }
	const descriptable*			annotates() const;

	/****************************************************************************/ 
	/*		protected functions													*/ 
	/****************************************************************************/ 
	protected:

	virtual void annotated();
	virtual bool acceptDescriptable ();

	/****************************************************************************/ 
	/*		protected fields													*/ 
	/****************************************************************************/ 
	protected:
	
	std::string			_name;
	descriptable*   	_descriptable;

	friend descriptable;

};

class annotations_map : public std::unordered_map<std::string,annotation*>
{

	/****************************************************************************/ 
	/*		constructor, destructor												*/ 
	/****************************************************************************/ 
	public:
	annotations_map ();
	virtual ~annotations_map ();

	

	/****************************************************************************/ 
	/*		searches															*/ 
	/****************************************************************************/ 	
	const annotation* get(const std::string& key) const;

	/****************************************************************************/ 
	/*		protected fields													*/ 
	/****************************************************************************/ 
	protected:

	bool _own_annotations ;	// if true, destroy annotations when destroyed

	friend descriptable;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif