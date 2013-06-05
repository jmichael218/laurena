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

#include "classesExamples.hpp"

using namespace laurena;

// global log
debug_stream GLOG;

//external functions
void ASimpleClass ();
void APolymorphicClass();
void AListClass ();

int main ()
{
	// log setting
	debug::_outputs.push_front(&std::cout);

    // laurena's initialization
    classes::init();
	json::JSON::init();

	buildClassDescriptor_SimpleCat();
	buildClassDescriptor_Animal();
	buildClassDescriptor_Cat();
	buildClassDescriptor_Zoo();

	classes::logClasses(GLOG);
	GLOG << std::endl;

	// to test ASimpleClass ();
	ASimpleClass();

	// to test APolymorphicClass ();
	APolymorphicClass();

	// To test lists
	AListClass();

	return 0;

}

