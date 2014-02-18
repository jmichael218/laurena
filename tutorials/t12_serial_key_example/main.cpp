///
/// \file     t12_serial_key.main.cpp
/// \brief    This example describes how to define a serial key shared by several classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This example describes how to define a serial key shared by several classes
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

class user
{
public:

    std::string     _name;
    std::string     _password;
    word32          _serial;

};

class bot : public unique
{
public:

    std::string     _id;
    word32          _serial;
};

descriptor* buildClassDescriptor_User()
{
    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->addField(&user::_name,"name");
    d->addField(&user::_password, "password");
    d->addField(&user::_serial, "serial");
    d->serialKeyField("serial");

    return d;
}

descriptor* buildClassDescriptor_Bot()
{
    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<bot>::build("bot");
    d->addField(&bot::_id,"id");
    d->addField(&bot::_serial, "serial");
    d->serialKeyField("serial");

    return d;
}

int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();


    return 1;
}