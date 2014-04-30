///
/// \file     t07_epoch_example.cpp
/// \brief    This example describes how to build a descriptor for a date
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  This example describes how to build a descriptor for a date
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

// We declare using the laurena lib's namespace
using namespace laurena;

// debug_stream is a customized ostream for debugging.
debug_stream GLOG;

//A global variable with date format strings
//Strings are not used in this example but the datetime_format is still required
std::shared_ptr<datetime_format> DATE_FORMAT;

//A class with an epoch field
// Epoch is the number of seconds since 1970.
class article 
{
public:

	article () : _epoch(0), _name() { };

	unsigned long long int  _epoch;
	std::string             _name;
};

void build_article_descriptor()
{
    // create class descriptor for the class 'article'
	auto d = standard_class_descriptor<article>::build("article");
	d->add_field(&article::_name,"name");
	d->add_field(&article::_epoch,"epoch").annotate(new format_epoch("format.all", "dd/mm/yyyy HH:MM:SS", DATE_FORMAT));
}

void test_article ()
{

	// let's create our dragon
	article watergate;
	watergate._name = "Watergate Scandal!";
	watergate._epoch = 74944888;

	// let's serialize our article !!
	std::string destination = json::json::serialize(watergate);

	// Let's display my jsoned dragon :
	std::cout << "Details of our article are :" << std::endl << destination << std::endl;

	// let's clone the article with marshalling
	article a;
	json::json::parse(destination,a);

	std::cout << "Cloned article details are : name=" << a._name << ", epoch=" << a._epoch << std::endl;
}


int main ()
{
    // log setting
    debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
    json::JSON::init();

    DATE_FORMAT = std::make_shared<datetime_format>();

    // let's declare the classes :
    build_article_descriptor();

    // Let's test the user class and its enum fields
    test_article();

    return 1;
}