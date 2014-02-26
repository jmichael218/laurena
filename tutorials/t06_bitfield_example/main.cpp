///
/// \file     t06_bitfield_example.cpp
/// \brief    This example describes how to build a descriptor for a 'bitfield' class field
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This example describes how to build a descriptor for a 'bitfield' class field
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

//A class with two kind of bitfield
class dragon 
{
public:

	dragon () : _state(0), _name() { _foods.resize(5); };

	unsigned char           _state;	// masks are 1 for 'happy', 2 for 'hungry', 4 for 'sleepy'
	boost::dynamic_bitset<> _foods; // 0 for knight, 1 for princess, 2 for cow, 3 for peasant, 4 for horse
	std::string             _name;
};

string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;

void buildClassDescriptor_Dragon()
{
    // create class descriptor for the class 'dragon'
	auto d = standard_class_descriptor<dragon>::build("dragon");
	d->add_field(&dragon::_name,"name");
	d->add_field(&dragon::_state,"state").annotate(new format_bitset("format.all", dragon_states));
	d->add_field(&dragon::_foods,"food").annotate(new format_bitset("format.all", dragon_foods));
}

void testDragon ()
{

	// let's create our dragon
	dragon smaug;
	smaug._name = "Smaug";
	smaug._state = 3 ; // hungry + happy
	smaug._foods.set(0); // smaug eat knights
	smaug._foods.set(4); // and horses

	// let's serialize smaug !!
	std::string destination = json::json::serialize(smaug);

	// Let's display my jsoned dragon :
	GLOG << "Details of our dragon are :" << std::endl << destination << std::endl;

	// let's clone smaug with marshalling
	dragon d;
	std::string states, foods;
	json::json::parse(destination,d);

	bitset::serialize((word64)d._state,dragon_states,states,",");
	bitset::serialize(d._foods,dragon_foods,foods,",");
	GLOG << "Cloned dragon details are : name=" << d._name << ", state=(" << states << "), foods=(" << foods << ")" << std::endl;


}


int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    // let's declare the classes :
    buildClassDescriptor_Dragon();

    // Let's test the user class and its enum fields
    testDragon();

    return 1;
}