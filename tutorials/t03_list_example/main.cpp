///
/// \file     t03_list_example.cpp
/// \brief    This example describes how to build a descriptor to serialize lists
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This example describes how to build a descriptor to serialize lists
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

// Here is our'animal' class
class animal
{
public:

    std::string     _specie;    //<! Name of the animal specie, like 'dog' or 'dragon'
    std::string     _name;      //<! Name of the animal
    unsigned char   _age;       //<! Age of the animal, in years

    bool operator == (const animal& source)
    { return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }
};

// Here is our list class : the zoo class which is a list of animal
class zoo : public std::list<animal>
{
};

// Here is our list class with pointers to animals
class circus : public std::list<animal*>
{
};

// This function register the animal class to the serialization and parsing system
void buildClassDescriptor_Animal ()
{
    // create class descriptor for the class 'animal'
    auto d_animal = standard_class_descriptor<animal>::build("animal");
    d_animal->addField(&animal::_specie,"specie");
    d_animal->addField(&animal::_name,"name");
    d_animal->addField(&animal::_age,"age");
}

// This function register the zoo class to the serialization and parsing system
void buildClassDescriptor_Zoo()
{
	auto d = list_descriptor<zoo,animal>::build("zoo");
}

// This function register the circus class to the serialization and parsing system
void buildClassDescriptor_Circus()
{
	auto d = list_descriptor<circus,animal*>::build("circus");
}

void testZoo()
{
	zoo z;

	animal a;
	a._specie = "lion";
	a._name   = "Rutger";
	a._age    = 7;
	z.push_front (a);

	a._specie = "elephant";
	a._name   = "Dora";
	a._age    = 45;
	z.push_front (a);

	a._specie = "crocodile";
	a._name   = "James" ;
	a._age    = 12;
	z.push_front(a);

	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned cat :
	GLOG << "Here is my zoo:" << std::endl << destination << std::endl;
	
	// Now let's instancing the zoo
	zoo z2;
	json::json::parse(destination,z2);

	GLOG << "Animals in my duplicated zoo are : " ;
	for (animal an : z2) GLOG << an._name << ", " ;
	GLOG << std::endl ;
}

void testCircus()
{
	circus z;

	animal a;
	a._specie = "turtle";
	a._name   = "Walter";
	a._age    = 7;
	z.push_front (&a);

    animal b;
	b._specie = "tiger";
	b._name   = "Gerald";
	b._age    = 45;
	z.push_front (&b);

    animal c;
	c._specie = "bear";
	c._name   = "Winnifred" ;
	c._age    = 12;
	z.push_front(&c);

	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned cat :
	GLOG << "Here is my circus:" << std::endl << destination << std::endl;
	
	// Now let's instancing the zoo
	circus z2;
	json::json::parse(destination,z2);

	GLOG << "Animals in my duplicated circus are : " ;
	for (animal* an : z2) GLOG << an->_name << ", " ;
	GLOG << std::endl ;
}

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    // let's declare the classes :
    buildClassDescriptor_Animal();
    buildClassDescriptor_Zoo();
    buildClassDescriptor_Circus();

    // Let's test the list<animal> class
    testZoo();

    // Let's test the list<animal*> class
    testCircus();

    return 1;
}