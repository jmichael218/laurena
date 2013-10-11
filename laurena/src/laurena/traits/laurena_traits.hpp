///
/// \file     laurena.hpp
/// \brief    Access to descriptor and serialization info through traits
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Access to descriptor and serialization info through traits
///

#ifndef LAURENA_LAURENA_TRAITS_H
#define LAURENA_LAURENA_TRAITS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/traits/type_traits.hpp>

#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/descriptor.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          basetype traits                                                      */ 
/*********************************************************************************/ 

template<typename T>
struct td
{
    static const descriptor* desc()
    {
        return nullptr;
    }

    static const descriptor* desc(T& t)
    {
		typedef traits<TYPENAME>::basetype basetype;
        return td<basetype>::desc ();
    }
};


template<typename TYPENAME>
const descriptor* desc_of(TYPENAME& t)
{
  typedef traits<TYPENAME>::basetype basetype;
  const descriptor* d = classes::byType(typeid(basetype));
  return d ? d : td<basetype>::desc();
}

template<typename TYPENAME>
bool is_pointer(TYPENAME& t)
{
	return false;
}

template<typename TYPENAME>
bool is_pointer(TYPENAME* t)
{
	return true;
}

#define field_descriptor(CLASSNAME,FIELD) ([] () -> const descriptor* { CLASSNAME ST_DESCRIPTOR; return desc_of(ST_DESCRIPTOR.FIELD); } ())
#define field_is_pointer(CLASSNAME,FIELD) ([] () -> bool { CLASSNAME ST_IS_POINTER; return is_pointer(ST_IS_POINTER.FIELD); } ())


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif