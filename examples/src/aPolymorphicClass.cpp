///
/// \file     aPolymorphicClass.cpp
/// \brief    an example how to serialize a derivated class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to serialize a derivated class
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

using namespace laurena;

extern debug_stream GLOG;

class animal
{
public:

	std::string		_specie;
	std::string		_name;
	unsigned char	_age;

	bool operator == (const animal& source)
	{ return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }
};

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

void APolymorphicClass ()
{
    // create class descriptor for the class 'animal'
	auto d_animal = standard_class_descriptor<animal>::build("animal");
	d_animal->init_field(animal,"specie",_specie);
    d_animal->init_field(animal,"name",_name);
    d_animal->init_field(animal,"age",_age);

	// create class descriptor for the class 'cat'
	// it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", d_animal);

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
    d->init_field(cat,"age",_age);
	d->init_field(cat,"birds",_birds);
	d->init_field(cat,"mouses",_mouses);

	// That's all. Now cat class is serializable in and from any supported language !

	// let's create a cat
	cat kitty;
	kitty._name = "Kitty";
	kitty._age  = 5;
	kitty._birds = 4;
	kitty._mouses = 14;

	// Let's serialize it into json
	std::string destination = json::json::serialize(kitty);

	// Let's display my jsoned cat :
	GLOG << "Here is my cat details:" << std::endl << destination << std::endl;

	// let's create a new cat from our serialized kitty 
	cat kimmie;
	json::json::parse(destination,kimmie);
	GLOG << "Kimmie is a " << kimmie._specie << " named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

	if (kimmie == kitty)
		GLOG << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
	else
		GLOG << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;


}

//End of file
