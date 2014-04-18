///
/// \file     t03_vector_example.cpp
/// \brief    This example describes how to build a descriptor to serialize vectors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This example describes how to build a descriptor to serialize vectors
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

// Here is our 'soldier' class
class soldier
{
public:

    std::string     _rank;    //<! Soldier rank or occupation like 'sergeant' or 'sniper'
    std::string     _name;    //<! Name of the soldier
    unsigned char   _age;     //<! Age of the soldier, in years

    bool operator == (const soldier& source)
    { return this->_rank == source._rank && this->_name == source._name && this->_name == source._name; }
};

// Here is our vector class : the army class which is a list of soldier
class army : public std::vector<soldier>
{
};

// Here is our list class with pointers to soldiers
class squad : public std::vector<soldier*>
{
};

// This function register the soldier class to the serialization and parsing system
void build_soldier_descriptor ()
{
    // create class descriptor for the class 'soldier'
    auto d = standard_class_descriptor<soldier>::build("soldier");
    d->add_field(&soldier::_rank,"rank");
    d->add_field(&soldier::_name,"name");
    d->add_field(&soldier::_age,"age");
}

// This function register the army class to the serialization and parsing system
// 'army' is a container of soldier
void build_army_descriptor()
{
	auto d = list_descriptor<army,soldier>::build("army");
}

// This function register the squad class to the serialization and parsing system
// 'squad' is a container of pointer to soldiers
void build_squad_descriptor()
{
	auto d = list_descriptor<squad,soldier*>::build("squad");
}

void test_army()
{
    army z;

    soldier a;
    a._rank = "Elite Private";
    a._name   = "John Rambi";
    a._age    = 17;
    z.push_back (a);

    a._rank   = "Elite Private";
    a._name   = "Chuck Norras";
    a._age    = 45;
    z.push_back (a);

    a._rank = "Captain";
    a._name   = "James T Kirk" ;
    a._age    = 32;
    z.push_back(a);

	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned army :
	GLOG << "Here is my army:" << std::endl << destination << std::endl;
	
	// Now let's instancing the army
	army z2;
	json::json::parse(destination,z2);

	GLOG << "Cloned soldiers in my duplicated army are : " ;
	for (soldier an : z2) GLOG << an._name << ", " ;
	GLOG << std::endl ;
}

void test_squad()
{
    squad z;

    soldier a;
    a._rank = "Sniper";
    a._name   = "Walter Jones";
    a._age    = 27;
    z.push_back (&a);

    soldier b;
    b._rank = "Sergeant";
    b._name   = "Gerald Magh";
    b._age    = 45;
    z.push_back (&b);

    soldier c;
    c._rank = "Major";
    c._name   = "Lee Smith" ;
    c._age    = 32;
    z.push_back(&c);

	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned squad :
	GLOG << "Here is my squad:" << std::endl << destination << std::endl;
	
	// Now let's instancing the squad
	squad z2;
	json::json::parse(destination,z2);

	GLOG << "Soldiers in my duplicated squad are : " ;
	for (soldier* an : z2) GLOG << an->_name << ", " ;
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
    build_soldier_descriptor();
    build_army_descriptor();
    build_squad_descriptor();

    // Let's test the vector<soldier> class
    test_army();

    // Let's test the vector<soldier*> class
    test_squad();

    return 1;
}