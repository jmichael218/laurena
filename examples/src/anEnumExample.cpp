///
/// \file     anEnumClass.cpp
/// \brief    an example how to define a numeric field as an enum
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to define a numeric field as an enum
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void AnEnumExample ()
{

	// let's create our user
	user Paulo;
	Paulo._age = 32;
	Paulo._gender = 0; // male
	Paulo._type = 1; // professor
	Paulo._name = "Paulo" ;

	// let's serialize Paulo !!
	std::string destination = json::json::serialize(Paulo);

	// Let's display my jsoned cat :
	GLOG << "Details of Paulo are :" << std::endl << destination << std::endl;

	// let's clone Paulo with marshalling
	user PauloCloned;
	json::json::parse(destination,PauloCloned);
	GLOG << "Paulo's clone details are : name=" << PauloCloned._name << ", gender=" << (genders [PauloCloned._gender]) << ", type=" << (user_types[PauloCloned._type]) << ", age=" << ((int) PauloCloned._age) << std::endl;


}

//End of file
