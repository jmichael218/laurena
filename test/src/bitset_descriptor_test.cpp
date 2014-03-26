///
/// \file     bitset_descriptor_test.cpp
/// \brief    Test boost::dynamic_bitset<> descriptor 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Test boost::dynamic_bitset<> descriptor 
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

struct TestBitset 
{
    word8 _w8;
    boost::dynamic_bitset<> _bitset;
    int32 _i32;
    
};

void testBitsetDescriptor()
{
    testunit::type("descriptor<boost::dynamic_bitset<>>");
    
    // is the descriptor existing ?
    testunit::start("is descriptor<boost::dynamic_bitset<>> defined ?");
    const descriptor* cd = td<string_array>::desc();
    testunit::end(cd != nullptr);

    testunit::start("serialize a dynamic bitset in binary format");
    test_bitset_binary tbb;
    tbb._w8 = 254;
    tbb._i32 = -5;
    tbb._bitset.resize(40);
    for (word8 i = 0; i < 40; i ++) 
        if (i&1)
            tbb._bitset.set(i);

    std::string serialized;
    oarchive_mdl::tostring(serialized, "testBitsetBinary", &tbb);
    testunit::log() << serialized << std::endl;   


    testunit::start("serialize a dynamic bitset in bitfield format");
    test_bitset_bitfield tbbf;
    tbbf._w16 = 65535;
    tbbf._i64 = -5;
    tbbf._bitset.resize(11);
    for (word8 i = 0; i < 11; i ++) 
        if (i&1)
            tbbf._bitset.set(i);
  
    oarchive_mdl::tostring(serialized, "testBitsetBitfield", &tbbf);
    testunit::log() << serialized << std::endl;   
}
//end of file
