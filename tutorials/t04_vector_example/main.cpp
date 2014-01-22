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

// Here is our'soldier' class
class soldier
{
public:

    std::string     _rank;    //<! Name of the animal specie, like 'dog' or 'dragon'
    std::string     _name;      //<! Name of the animal
    unsigned char   _age;       //<! Age of the animal, in years

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

// This function register the animal class to the serialization and parsing system
void buildClassDescriptor_Soldier ()
{
    // create class descriptor for the class 'animal'
    auto d = standard_class_descriptor<soldier>::build("soldier");
    d->addField(&soldier::_rank,"rank");
    d->addField(&soldier::_name,"name");
    d->addField(&soldier::_age,"age");
}

// This function register the zoo class to the serialization and parsing system
void buildClassDescriptor_Army()
{
	auto d = list_descriptor<army,soldier>::build("army");
}

// This function register the circus class to the serialization and parsing system
void buildClassDescriptor_Squad()
{
	auto d = list_descriptor<squad,soldier*>::build("squad");
}

void testArmy()
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

void testSquad()
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

	// Let's display my jsoned cat :
	GLOG << "Here is my squad:" << std::endl << destination << std::endl;
	
	// Now let's instancing the zoo
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
    buildClassDescriptor_Soldier();
    buildClassDescriptor_Army();
    buildClassDescriptor_Squad();

    // Let's test the vector<soldier> class
    testArmy();

    // Let's test the vector<soldier*> class
    testSquad();

    return 1;
}