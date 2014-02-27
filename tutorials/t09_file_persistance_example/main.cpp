///
/// \file     t09_file_persistance_example.cpp
/// \brief    This example describes how to set up and use a file based persistance engine
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This example describes how to set up and use a file based persistance engine
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

// Let's reuse our user class from the enum example
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

descriptor* buildClassDescriptor_User()
{
    auto denum = enum_type_descriptor<gender>::build("gender", genders);

    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->add_field(&user::_gender,"gender");
    d->add_field(&user::_type,"type").annotate(new format_enum("format.all",user_types));
    d->add_field(&user::_age,"age");
    d->add_field(&user::_name,"name");

    //Let"s declare name as the primary field.
    d->primary_key("name");
    return d;
}

persistance DISK;

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    // user class initialization
    descriptor* userDescriptor = buildClassDescriptor_User();

    // user persistance initialization
    DISK.add("user", std::make_shared<json::json_dao>(*userDescriptor, "datas/users"));

    // let's create a user
    user bob;
    bob._age = 25;
    bob._gender = MALE;
    bob._name = "Bob Joe";
    bob._type = 1; // professor

    // let's save it on disk
    DISK.insert("user", bob);

    // let's test the read function
    user bobcloned;
    DISK.select("user", "Bob Joe", &bobcloned);

    // Let's serialize it into json
    std::string destination = json::json::serialize(bobcloned);

    // Let's check create + read worked :
    GLOG << "Here is Bob's details:" << std::endl << destination << std::endl;
    return 1;
}