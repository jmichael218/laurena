///
/// \file     main.cpp
/// \brief    Main file for the examples
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Main file for the examples
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

using namespace laurena;

// global log
debug_stream GLOG;

//external functions
void ASimpleClass ();
void APolymorphicClass();

int main ()
{
	// log setting
	debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
	json::JSON::init();

	// to test ASimpleClass ();
	//ASimpleClass();

	// to test APolymorphicClass ();
	APolymorphicClass();

	return 0;

}

