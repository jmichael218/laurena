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
    d->primaryKeyField("name");

    return d;
}

descriptor* buildClassDescriptor_Bot()
{
    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<bot>::build("bot");
    d->addField(&bot::_id,"id");
    d->addField(&bot::_serial, "serial");
    d->serialKeyField("serial");
    d->primaryKeyField("id");

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

    descriptor* userDescriptor = buildClassDescriptor_User();
    descriptor* botDescriptor = buildClassDescriptor_Bot();

    dao::sptr user_dao (new json::json_dao(*userDescriptor, "datas/users"));
    user_dao->serial_manager("serials");

    dao::sptr bot_dao = std::make_shared<json::json_dao>(*botDescriptor,  "datas/bots");
    bot_dao->serial_manager("serials");

    DISK.add("user", user_dao);
    DISK.add("bot",  bot_dao);

    DISK.add("serials", std::make_shared<file_serial_manager>("serials", json::JSON::language(), "datas/serials"));

    // let's create a user
    user bob;
    bob._name = "Bob Joe";
    bob._password = "azerty";
    bob._serial = 1;

    // let 's create a bot
    bot robby;
    robby._id = "Robby";
    robby._serial = 2;

    // let's save it on disk
    DISK.insert("user", &bob);
    DISK.insert("bot", &robby);


    any res = DISK.serial_to_object("serials", "1");
    user* bob_clone = anycast<user*>(res);

    res = DISK.serial_to_object("serials", "2");
    bot* robby_clone = anycast<bot*>(res);

    return 1;
}