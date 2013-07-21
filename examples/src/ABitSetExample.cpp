///
/// \file     ABitSetExample.cpp
/// \brief    an example how to define a numeric field as a bitset
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to define a numeric field as a bitset
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void ABitSetExample ()
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

//End of file
