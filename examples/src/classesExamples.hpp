///
/// \file     classesExamples.hpp
/// \brief    Classes for JSON examples
/// \author   Frederic Manisse
/// \version  1.0
///
/// Classes for JSON examples
///
#ifndef LAURENA_EXAMPLES_CLASSES_H
#define LAURENA_EXAMPLES_CLASSES_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

/********************************************************************************/ 
/*			examples classes                                                    */ 
/********************************************************************************/ 

class simple_cat 
{
public:

	std::string		_name;
	unsigned char	_age;
	unsigned int	_birds;
	unsigned int	_mouses;

	bool operator==(const simple_cat& c)
	{
		return this->_name == c._name && this->_age == c._age && this->_birds == c._birds && this->_mouses == c._mouses ;
	}
};
void buildClassDescriptor_SimpleCat ();

class animal
{
public:

	std::string		_specie;
	std::string		_name;
	unsigned char	_age;

	bool operator == (const animal& source)
	{ return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }

	animal& operator = (const animal& source)
	{ this->_age = source._age ; this->_specie = source._specie; this->_name = source._name; return *this; }
};
void buildClassDescriptor_Animal();

class zoo : public std::list<animal>
{
};
void buildClassDescriptor_Zoo();

class circus : public std::vector<animal>
{
};
void buildClassDescriptor_Circus();

class cat : public animal
{
public:

	unsigned int	_birds;
	unsigned int	_mouses;

	cat () : animal () 
	{ this->_specie = "cat" ;  }

	bool operator==(const cat& c)
	{ return this->animal::operator==(c) && this->_birds == c._birds && this->_mouses == c._mouses ; }
};
void buildClassDescriptor_Cat();




/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

#endif
//end of file
