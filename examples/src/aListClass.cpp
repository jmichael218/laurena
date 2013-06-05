///
/// \file     aListClass.cpp
/// \brief    an example how to serialize a list
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to serialize a list
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void AListClass ()
{

	// That's all. Now cat class is serializable in and from any supported language !
	zoo z;

	animal a;
	a._specie = "lion";
	a._name   = "Rutger";
	a._age    = 7;
	z.push_front (a);

	a._specie = "elephant";
	a._name   = "Dora";
	a._age    = 45;
	z.push_front (a);

	a._specie = "crocodile";
	a._name   = "James" ;
	a._age    = 12;
	z.push_front(a);

	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned cat :
	GLOG << "Here is my zoo:" << std::endl << destination << std::endl;
	
	// Now let's instancing the zoo
	zoo z2;
	json::json::parse(destination,z2);

	GLOG << "Animals in my other zoo are : " ;
	for (animal an : z2) GLOG << an._name << ", " ;
	GLOG << std::endl ;


}

//End of file