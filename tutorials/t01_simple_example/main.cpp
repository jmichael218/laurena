///
/// \file     t01_simple_example.main.cpp
/// \brief    A single simple example of a POD class descriptor, serialization and parsing to json
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A single simple example of a POD class descriptor, serialization and parsing to json
///

#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;


// Here is our test class
class simple_cat 
{
public:

    std::string     _name;      //<! name of the cat
    unsigned char   _age;       //<! Age of the cat
    unsigned int    _birds;     //<! birds killed
    unsigned int    _mouses;    //<! mouses hunted

    // This operator will be used to validate a parsed cat is equal to the source
    bool operator==(const simple_cat& c)
    {
	    return this->_name == c._name && this->_age == c._age && this->_birds == c._birds && this->_mouses == c._mouses ;
    }
};

// This function register the simple_cat to the serialization and parsing system
void buildClassDescriptor_SimpleCat ()
{

    // create class descriptor for the class 'cat'
    // syntax to create a class descriptor for a simple class made of POD fields is standard_class_descriptor<CLASS>::build("classname");
    // calling ::build will also add the class descriptor to the global classes list.
    auto d = standard_class_descriptor<simple_cat>::build("simple_cat");

    // to be able to serialize fields, call descriptor->addField(FIELD, "fieldname")
    d->addField(&simple_cat::_name,"name");
    d->addField(&simple_cat::_age,"age");
    d->addField(&simple_cat::_birds,"birds");
    d->addField(&simple_cat::_mouses,"mouses");
}

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();


    // let's declare the simple_cat class :
    buildClassDescriptor_SimpleCat();

    // let's create a cat
    simple_cat kitty;
    kitty._name = "Kitty";
    kitty._age  = 5;
    kitty._birds = 4;
    kitty._mouses = 14;

    // Let's serialize it into json
    std::string destination = json::json::serialize(kitty);

    // Let's display my jsoned cat :
    GLOG << "Here is my cat details:" << std::endl << destination << std::endl;

    // let's create a new cat from our serialized kitty 
    simple_cat kimmie;
    json::json::parse(destination,kimmie);
    GLOG << "Kimmie is named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

    if (kimmie == kitty)
        GLOG << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
    else
        GLOG << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;

    return 1;
}
//End of file
