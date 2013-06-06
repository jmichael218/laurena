///
/// \file     aVectorClass.cpp
/// \brief    an example how to serialize a vector
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to serialize a vector
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void AVectorClass ()
{

	circus c;
	c.resize(3);
	
	c[0]._specie = "lion";
	c[0]._name   = "Ryan";
	c[0]._age    = 6;


	c[1]._specie = "horse";
	c[1]._name   = "Tornado";
	c[1]._age    = 8;

	c[2]._specie = "tiger";
	c[2]._name   = "Sandy" ;
	c[2]._age    = 12;

	// Let's serialize it into json
	std::string destination = json::json::serialize(c);

	// Let's display my jsoned circus :
	GLOG << "Here is my circus:" << std::endl << destination << std::endl;
	
	// Now let's instancing the circus
	circus c2;
	json::json::parse(destination,c2);

	GLOG << "Animals in my other circus are : " ;
	for (animal an : c2) GLOG << an._name << ", " ;
	GLOG << std::endl ;


}

//End of file