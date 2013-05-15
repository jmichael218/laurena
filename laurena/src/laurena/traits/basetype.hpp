///
/// \file     basetype.hpp
/// \brief    Get the base type of a type like const int * => int
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Get the base type of a type like const int * => int
///

#ifndef LAURENA_BASETYPE_H
#define LAURENA_BASETYPE_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          basetype traits                                                      */ 
/*********************************************************************************/ 

template<typename VALUETYPE>
struct basetype
{
    typedef typename boost::remove_pointer< typename boost::remove_reference<typename boost::remove_const<VALUETYPE>::type>::type>::type type;
};

template<>
struct basetype<void*>
{
    typedef void type;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif