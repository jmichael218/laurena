///
/// \file     shared_pointer_test.cpp
/// \brief    Test shared_pointer class member serialization
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Test shared_pointer class member serialization
//
#include <laurena/laurena.hpp>
#include <laurena/mdl/mdl.hpp>
#include "character.hpp"

using namespace laurena;
using namespace test;
using namespace mdl;

/*
class avatar
{
public:

    std::shared_ptr<character>  _player;
    std::shared_ptr<character>  _character;
*/
void testSharedPointerFields ()
{
    /****************************************************************************/ 
    /*          test shared pointer fields                                      */ 
    /****************************************************************************/ 
    std::shared_ptr<character>  pl = std::make_shared<character>();
    pl->_name = "Reeloy Kenjins";
    pl->_age  = 15;

    std::shared_ptr<character>  ch = std::make_shared<character>();
    ch->_name = "Lord Gardakan";
    ch->_age  = 57;

    avatar a;
    a._player = pl;
    //a._character = ch;

    std::string serialized_avatar;
    oarchive_mdl::tostring(serialized_avatar, "avatar", &a);
    testunit::log() << serialized_avatar << std::endl;    

    avatar b;
	laurena::mdl::mdl::parse(serialized_avatar, b);

    /****************************************************************************/ 
    /*          test shared pointer as list elements                            */ 
    /****************************************************************************/ 
    avatars as;
    avatar::sptr sas = std::make_shared<avatar>();
    sas->_player = pl;
    sas->_character = ch;
    as.push_back(sas);

    oarchive_mdl::tostring(serialized_avatar, "avatars", &as);
    testunit::log() << serialized_avatar << std::endl;   

    avatars sb;
	laurena::mdl::mdl::parse(serialized_avatar, sb);


    return;
}

//End of file
