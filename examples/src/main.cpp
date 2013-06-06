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
void AVectorClass ();
void AnEnumExample ();
void ABitSetExample();

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
	buildClassDescriptor_Circus();
	buildClassDescriptor_User();
	buildClassDescriptor_Dragon();


	classes::logClasses(GLOG);
	GLOG << std::endl;

	// to test ASimpleClass ();
	ASimpleClass();

	// to test APolymorphicClass ();
	APolymorphicClass();

	// To test lists
	AListClass();

	// To test vector
	AVectorClass ();

	// Example of an enum field
	AnEnumExample();

	// Example of bitset fields
	ABitSetExample();

	return 0;

}

