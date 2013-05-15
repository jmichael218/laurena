///
/// \file     mdl_serialization_test.cpp
/// \brief    test functions for the mdl language
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// test functions for the mdl language
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testBasicMdlSerialization ()
{
    character bob;
    bob._name = "Bob" ;
    bob._age = 28;

    testunit::type("MDL - simple object");
    testunit::function("oarchive_mdl::toString + iarchive_mdl::fromString - simple object");

    std::string serialized_bob;
    oarchive_mdl::tostring(serialized_bob, "character", &bob);

    testunit::log() << serialized_bob << std::endl;

    character bob2;
    any a2 = &bob2;
    iarchive_mdl::fromString(serialized_bob.c_str(),"character",a2);
    
    testunit::endTest(bob2._name == "Bob" && bob2._age == 28 );

    return;
}

void testMdl()
{
    testBasicMdlSerialization();
}
