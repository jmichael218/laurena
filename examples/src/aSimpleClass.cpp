///
/// \file     aSimpleClass.cpp
/// \brief    an example how to serialize a simple class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to serialize a simple class
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

using namespace laurena;

extern debug_stream GLOG;

class cat 
{
public:

	std::string		_name;
	unsigned char	_age;
	unsigned int	_birds;
	unsigned int	_mouses;

	bool operator==(const cat& c)
	{
		return this->_name == c._name && this->_age == c._age && this->_birds == c._birds && this->_mouses == c._mouses ;
	}
};

void ASimpleClass ()
{
    // create class descriptor for the class 'cat'
	// syntax to create a class descriptor for a simple class made of POD fields is standard_class_descriptor<CLASS>::build("classname");
	// calling ::build will also add the class descriptor to the global classes list.
    auto d = standard_class_descriptor<cat>::build("cat");

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
    d->init_field(cat,"name",_name);
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
	GLOG << "Kimmie is named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

	if (kimmie == kitty)
		GLOG << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
	else
		GLOG << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;


}

//End of file
