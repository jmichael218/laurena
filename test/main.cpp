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
#include <laurena/sql/sql.hpp>

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
void test_sql();
void testMdlParameterArray();
void testMdlPArray();
void testMdlList ();
void testJsonlList();
void testJSonNoWrapper();
void testJsonAny();
void testBoolDescriptor ();
void testVelocity();
void testStringArrayGetFieldValue();
void testNewFieldInit();
void testParameters();


extern void cstring_test ();

const string_array the_tens = "zero one two three four five six seven eight nine ten";

void buildTestClassDescriptors ()
{

    /****************************************************************************/ 
    /*          build class character descriptor                                */ 
    /****************************************************************************/ 
    auto d = standard_class_descriptor<character>::build("character");
	d->annotate(new sql::sql_tablename("characters"));
    d->add_field(&character::_name, "name")
		.annotate(new sql::sql_column("name", sql::sql_column::PRIMARY_KEY))		
		;
    d->add_field(&character::_age, "age")
		.annotate(new sql::sql_column("age"))	
		;

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
	dm->add_field(&mariage::_husband,"husband");
	dm->add_field(&mariage::_wife,"wife");
	dm->add_field(&mariage::_children,"children");



    /****************************************************************************/ 
    /*          build class test_bitset_binary descriptor                       */ 
    /****************************************************************************/ 
    auto d3 = standard_class_descriptor<test_bitset_binary>::build("test_bitset_binary");
    d3->add_field(&test_bitset_binary::_w8,"w8");
    d3->add_field(&test_bitset_binary::_bitset,"bitset");
    d3->add_field(&test_bitset_binary::_i32,"i32");

    /****************************************************************************/ 
    /*          build class test_bitset_bitfield descriptor                     */ 
    /****************************************************************************/
    auto d4 = standard_class_descriptor<test_bitset_bitfield>::build("test_bitset_bitfield");
    d4->add_field(&test_bitset_bitfield::_w16,"w16");
    d4->add_field(&test_bitset_bitfield::_bitset,"bitset").annotate(new format_bitset("format.all", the_tens));
    d4->add_field(&test_bitset_bitfield::_i64,"i64");


    /****************************************************************************/ 
    /*          build class test_bool descriptor								*/ 
    /****************************************************************************/
    auto d5 = standard_class_descriptor<test_bool>::build("test_bool");
    d5->add_field(&test_bool::_a,"a");
    d5->add_field(&test_bool::_b,"b");

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

	testParameters();
	testNewFieldInit();

    // running tests
    testNumericDescriptors ();
    testMdl();
	testJson();
    testanyDescriptor();
    testStringArrayDescriptor();
    testBitsetDescriptor();
	//test_sql();

    testunit::displayResults();
    return 0;
}

//End of file
