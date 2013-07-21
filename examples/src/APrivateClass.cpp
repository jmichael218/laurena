///
/// \file     aPrivateClass.cpp
/// \brief    an example how to serialize a class with private / protected field
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

class TP
{
	public:
		int _a;
	protected:
		int _b;
};

class TPU : public TP
{
	friend void TTP();
};


void TTP()
{
	int TPU::* pi;

	pi = &TPU::_a ;
	pi = &TPU::_b;

}

void AGetterAndSetterExample ()
{
	building b;
	b.name ("Town House");
	b.floors(3);

	// Let's serialize it into json
	std::string destination = json::json::serialize(b);

	// Let's display my jsoned building :
	GLOG << "Here is my building details:" << std::endl << destination << std::endl;



	// let's create a new building from the serialized one
	building b2;
	json::json::parse(destination,b2);

	GLOG << "Building 2 is '" << b2.name() << "' and has " << ((int)b2.floors()) << " floors." << std::endl;
}

