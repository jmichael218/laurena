///
/// \file     any_descriptor_test.cpp
/// \brief    Test numeric type descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test numeric type descriptors
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

void testanyDescriptor ()
{
    variable_list vl ;


    variable v;
    v._name = "employee";
    character bob;
    bob._name = "bob" ;
    bob._age = 38 ;
    v._value = &bob;

        
    std::string serialized_employee;
    oarchive_mdl::tostring(serialized_employee, "character", &v);
    testunit::log() << serialized_employee << std::endl;    


    vl.add("employee",&bob);
    vl.add("company","World Company");
    vl.add("location","Paris");

    std::string serialized_list;
    any ao;
    ao = &vl ;
    oarchive_mdl::tostring(serialized_list,"variables",ao);
    testunit::log() << serialized_list << std::endl;  

    return ;
}

//End of file
