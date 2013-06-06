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

class user
{
public:
	
	unsigned char	_gender; // 0 for male, 1 for female
	unsigned int	_type;   // 0 for student, 1 for professor, 2 for visitor
	unsigned int	_age;
	std::string	_name;

};

void buildClassDescriptor_User();
extern laurena::string_array genders ;
extern laurena::string_array user_types ;

class dragon 
{
public:

	dragon () : _state(0), _name() { _foods.resize(5); };

	unsigned char			_state;	// mask are 1 for 'happy', 2 for 'hungry', 3 for 'sleepy'
	boost::dynamic_bitset<>	_foods; // 0 for knight, 1 for princess, 2 for cow, 3 for peasant, 4 for horse
	std::string				_name;
};
void buildClassDescriptor_Dragon();
extern laurena::string_array dragon_states;
extern laurena::string_array dragon_foods;




/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

#endif
//end of file
