///
/// \file     t02_polymorphic_example.main.cpp
/// \brief    This example describes how to build descriptor for polymorphic classes, i.e a parent class and a child class.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This example describes how to build descriptor for polymorphic classes, i.e a parent class and a child class.
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

// Here is our parent class : an 'animal' class
class animal
{
public:

    std::string     _specie;    //<! Name of the animal specie, like 'dog' or 'dragon'
    std::string     _name;      //<! Name of the animal
    unsigned char   _age;       //<! Age of the animal, in years

    bool operator == (const animal& source)
    { return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }
};

// Here is our child class : a cat class derivated from 'animal'
class cat : public animal
{
public:

    unsigned int    _birds;     //<! Birds killed by the cat
    unsigned int    _mouses;    //<! Mouses killed by the cat

    //<! Constructor : set specie
    cat () : animal ()  
    { this->_specie = "cat" ;  }

    //<! == operator
    bool operator==(const cat& c)
    { return this->animal::operator==(c) && this->_birds == c._birds && this->_mouses == c._mouses ; }
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


// This function register the cat class to the serialization and parsing system
void buildClassDescriptor_Cat ()
{
    // create class descriptor for the class 'cat'
    // it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", td<animal>::desc());
    d->addField(&cat::_birds,"birds");
    d->addField(&cat::_mouses,"mouses");
}

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    // let's declare the animal class :
    buildClassDescriptor_Animal();

    // let's declare the cat class :
    buildClassDescriptor_Cat();

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
    std::cout << "Kimmie is a " << kimmie._specie << " named " << kimmie._name 
              << ", has " << ((int)kimmie._age) << " years, killed " 
              << kimmie._birds << " birds and " << kimmie._mouses << " mouses." 
              << std::endl;

    // LEt's control if kimmie is exactly the same than kitty
    if (kimmie == kitty)
        GLOG << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
    else
        GLOG << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;

    return 1;

}
//End of file
