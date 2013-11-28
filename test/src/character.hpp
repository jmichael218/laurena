///
/// \file     character.hpp
/// \brief    test classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  test classes
///

#ifndef LAURENA_TEST_CHARACTER_H
#define LAURENA_TEST_CHARACTER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace test {

class character
{
public:

    std::string     _name;
    word16          _age;

};

class characters : public std::vector<character*>
{

};

class mariage 
{
public:

	mariage () : _husband (nullptr) , _wife (nullptr) {}

	character*	_husband;
	character*	_wife;
	characters	_children;
};




class test_bitset_binary
{
public:

    word8                       _w8;
    boost::dynamic_bitset<>     _bitset;
    int32                       _i32;
};


class test_bitset_bitfield
{
public:

    word16                      _w16;
    boost::dynamic_bitset<>     _bitset;
    int64                       _i64;

};

class LWord32 : public std::list<word32>
{ };

class LString : public std::list<std::string>
{ };
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif