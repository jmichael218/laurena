///
/// \file     aPolymorphicClass.cpp
/// \brief    an example how to serialize a derivated class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to serialize a derivated class
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void APolymorphicClass ()
{

	// let's create a cat
	cat kitty;
	kitty._name = "Kitty";
	kitty._age  = 5;
	kitty._birds = 4;
	kitty._mouses = 14;

	// Let's serialize it into json
	std::string destination = json::json::serialize(kitty);

	// Let's display my jsoned cat :
	GLOG << "Here is my cat details:" << std::endl << destination << std::endl;

	// let's create a new cat from our serialized kitty 
	cat kimmie;
	json::json::parse(destination,kimmie);
	GLOG << "Kimmie is a " << kimmie._specie << " named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

	if (kimmie == kitty)
		GLOG << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
	else
		GLOG << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;


}

//End of file
