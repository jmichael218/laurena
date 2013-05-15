///
/// \file     method_descriptor.hpp
/// \brief    Describe a serializable call to a method member in a class 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable call to a method member in a class 
///
#ifndef LAURENA_METHOD_DESCRIPTOR_H
#define LAURENA_METHOD_DESCRIPTOR_H

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

#include <laurena/descriptors/descriptor.hpp>
#include <laurena/toolboxes/bitset.hpp>
#include <laurena/memory/memory_functions.hpp>
#include <laurena/types/any.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/*********************************************************************************/
/*          method_descriptor                                                    */ 
/*********************************************************************************/ 

class method_descriptor
{
public:
    
    method_descriptor (const std::string& name);
    virtual ~method_descriptor ();

    inline const std::string& name() { return this->_name ; }

    virtual any& invoke(any& destination, any& object)              const;
    virtual any& invoke(any& destination, any& object, any& param0) const;
    virtual any& invoke(any& destination, any& object, any& param0, any& param1) const;

protected:

    void raisesError() const;

    std::string     _name;

};

/********************************************************************************/ 
/*      method_table                                                            */ 
/********************************************************************************/

class method_table : public std::unordered_map<std::string, method_descriptor*>
{
public:



    virtual ~method_table () {}

};



//typedef  int (Fred::*FredMemFn)(char x, float y);
// typedef std::string& (std::string::* funname) (

/*
template<typename RETURN, typename OBJECT, typename PARAM0>
class method_descriptor_R1 : public method_descriptor
{
protected:

    typedef RETURN (OBJECT::* method_ptr_type) (PARAM0);
    method_ptr_type _funptr;

public:

    method_descriptor_R1 (const std::string& name, method_ptr_type ptr) : method_descriptor (name) 
    {
        _funptr = ptr;
    }

    virtual ~method_descriptor_R1 ()
    { }

    virtual any& invoke(any& object, any& param0, any& destination)  const
    {
        OBJECT* o = anycast<OBJECT*>(object);
        PARAM0  p = anycast<PARAM0>(param0);
        destination = ((*o).*(_funptr)) (p);
        return destination;
    }
};

template<typename RETURN, typename OBJECT, typename PARAM0, typename PARAM1>
class MethodDescriptor_CR2 : public MethodDescriptor
{
protected:

    typedef RETURN (OBJECT::* MethodPtrType) (PARAM0, PARAM1) const;
    MethodPtrType _funptr;

public:

    MethodDescriptor_CR2 (const std::string& name, MethodPtrType ptr) : MethodDescriptor (name) 
    {
        _funptr = ptr;
    }

    virtual ~MethodDescriptor_CR2 ()
    { }

    virtual Any& invoke(Any& object, Any& param0, Any& param1, Any& destination)  const
    {
        OBJECT* o = anycast<OBJECT*>(object);
        PARAM0  p0 = anycast<PARAM0>(param0);
        PARAM1  p1 = anycast<PARAM1>(param1);
        destination = ((*o).*(_funptr)) (p0, p1);
        return destination;
    }
};
*/ 
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif 