///
/// \file     ACustomizedTypeFormat.cpp
/// \brief    an example how to customize string format of a class for a given class or for a given field
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// an example how to customize string format of a class for a given class or for a given field
//
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

extern debug_stream GLOG;

void ACustomizedTypeFormat ()
{
	itriangle t;

	t._v0._x = 1;  t._v0._y = 2;
	t._v1._x = 3;  t._v1._y = 4;
	t._v2._x = 5; t._v2._y = 6;

	
	// let's serialize our triangle
	std::string destination = json::json::serialize(t);

	// Let's display my jsoned triangle :
	GLOG << "Our triangle is :" << std::endl << destination << std::endl;

	// let's marshall it in a new triangle
	itriangle t2;
	json::json::parse(destination,t2);
	GLOG << "Our new triangle is : v0=" << t2._v0 << ", v1=" << t2._v1 << ", v2=" << t2._v2 << std::endl;
}