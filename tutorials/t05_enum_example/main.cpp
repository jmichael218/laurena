///
/// \file     t05_enum_example.cpp
/// \brief    This example describes how to build a descriptor for an 'enum' class field
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This example describes how to build a descriptor for an 'enum' class field
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;


enum gender : unsigned char
{
    UNDEFINED,
    MALE,
    FEMALE
};

class user
{
public:
	
    gender          _gender; // a true enum
    unsigned int    _type;   // 0 for student, 1 for professor, 2 for visitor
    unsigned int    _age;
    std::string	    _name;

};

string_array genders    = "undefined male female" ;
string_array user_types = "student professor visitor" ;

void build_user_descriptor()
{
    auto denum = enum_type_descriptor<gender>::build("gender", genders);

    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->add_field(&user::_gender,"gender");
    d->add_field(&user::_type,"type").annotate(new format_enum("format.all",user_types));
    d->add_field(&user::_age,"age");
    d->add_field(&user::_name,"name");
}

void test_user ()
{

    // let's create our user
    user Paulo;
    Paulo._age = 32;
    Paulo._gender = MALE; // male
    Paulo._type = 1; // professor
    Paulo._name = "Paulo" ;

    // let's serialize Paulo !!
    std::string destination = json::json::serialize(Paulo);

    // Let's display my jsoned Paulo :
    std::cout << "Details of Paulo are :" << std::endl << destination << std::endl;

    // let's clone Paulo with marshalling
    user PauloCloned;
    json::json::parse(destination,PauloCloned);

    std::cout << "Paulo's clone details are : name=" << PauloCloned._name 
         << ", gender=" << (genders [PauloCloned._gender]) 
         << ", type=" << (user_types[PauloCloned._type]) 
         << ", age=" << ((int) PauloCloned._age) 
         << std::endl;
}

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    // let's declare the classes :
    build_user_descriptor();

    // Let's test the user class and its enum fields
    test_user();

    return 1;
}