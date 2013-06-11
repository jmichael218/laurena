///
/// \file     main.cpp
/// \brief    Main file for the test program that validate implementation of the laurena library
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Main file for the test program that validate implementation of the laurena library
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include <laurena/json/json.hpp>

#include "src/character.hpp"

using namespace laurena;
using namespace test;

debug_stream GLOG;

void testNumericDescriptors ();
void testMdl();
void testanyDescriptor ();
void testStringArrayDescriptor();
void testBitsetDescriptor();
void testMDL();
void testJson();


extern void cstring_test ();

const string_array the_tens = "zero one two three four five six seven eight nine ten";

void buildTestClassDescriptors ()
{

    /****************************************************************************/ 
    /*          build class character descriptor                                */ 
    /****************************************************************************/ 
    auto d = standard_class_descriptor<character>::build("character");
    d->init_field(character,"name",_name);
    d->init_field(character,"age",_age);

    // testing descriptors
    const descriptor* d2 = classes::byName("character");
    character bob ;    
    d2->setObjectField(&bob,"name",std::string("Bob"));
    d2->setObjectField(&bob,"age",31);

    GLOG << "His name is " << bob._name << " and his age is " << bob._age << std::endl ;

	/****************************************************************************/
	/*			build characters vector descriptor								*/ 
	/****************************************************************************/ 
	auto dchs = new vector_descriptor<characters,character*>("characters");
	classes::add(dchs);

	/****************************************************************************/
	/*			build class mariage descriptor									*/ 
	/****************************************************************************/ 
	auto dm = standard_class_descriptor<mariage>::build("mariage");
	dm->init_field(mariage,"husband",_husband);
	dm->init_field(mariage,"wife",_wife);
	dm->init_field(mariage,"children",_children);



    /****************************************************************************/ 
    /*          build class test_bitset_binary descriptor                       */ 
    /****************************************************************************/ 
    auto d3 = standard_class_descriptor<test_bitset_binary>::build("test_bitset_binary");
    d3->init_field(test_bitset_binary,"w8",_w8);
    d3->init_field(test_bitset_binary,"bitset",_bitset);
    d3->init_field(test_bitset_binary,"i32",_i32);

    /****************************************************************************/ 
    /*          build class test_bitset_bitfield descriptor                     */ 
    /****************************************************************************/
    auto d4 = standard_class_descriptor<test_bitset_bitfield>::build("test_bitset_bitfield");
    d4->init_field(test_bitset_bitfield,"w16",_w16);
    d4->init_field(test_bitset_bitfield,"bitset",_bitset).isBitSet(the_tens);
    d4->init_field(test_bitset_bitfield,"i64",_i64);

}


int main ()
{


    // laurena's initialization
    classes::init();
    mdl::MDL::init();
	json::JSON::init();

    // setting test & log configuration
    debug::_outputs.push_front(&std::cout);
    GLOG << "testing core laurena library." << std::endl ;
    testunit::setLogger(&GLOG);



    // build descriptors for test classes
    buildTestClassDescriptors();

    // toolboxes tests
    cstring_test ();

    // running tests
    testNumericDescriptors ();
    testMdl();
	testJson();
    testanyDescriptor();
    testStringArrayDescriptor();
    testBitsetDescriptor();

    testunit::displayResults();
    return 0;
}

//End of file
