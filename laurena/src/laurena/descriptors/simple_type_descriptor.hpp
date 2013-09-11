///
/// \file     simple_type_descriptor.hpp
/// \brief    int and other number types descriptor template
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// int and other number types descriptor template
///

#ifndef LAURENA_SIMPLE_TYPE_DESCRIPTOR_H
#define LAURENA_SIMPLE_TYPE_DESCRIPTOR_H

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
#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
#include <laurena/traits/laurena_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          simple_type_descriptor                                               */ 
/*********************************************************************************/ 
template< typename T >
class simple_type_descriptor : public descriptor 
{
public:
    
    /****************************************************************************/ 
    /*          constructor, destructor                                         */ 
    /****************************************************************************/ 
    simple_type_descriptor (const char* name);

    /****************************************************************************/ 
    /*          virtual functions from ClassDescriptor                         */ 
    /****************************************************************************/ 

    // ACCESSORS
    virtual size_t  sizeOf()            const;
    virtual bool    has(descriptor::Flags flag) const;

	//CAST
	virtual any		cast (const any& value) const;

    // RAW VALUE SERIALIZATION
    virtual void            set(void* ptr, const any& value)  const;
    virtual any&            get(void* ptr, any& value)  const;

	// OPERATORS
	virtual bool equals(const any& a0, const any& a1) const;

    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
	virtual any&            stoa(const std::string& string_value, any& value) const;
       
    // OBJECT CONSTRUCTOR FOR INJECTION 
    virtual any& clear(any& value) const;
    virtual any create() const;
};

/********************************************************************************/ 
/*          templated code                                                      */ 
/********************************************************************************/ 

// CONSTRUCTOR
template<typename T>
simple_type_descriptor<T>::simple_type_descriptor (const char* name) : descriptor(name, typeid(T))
{
}

// ACCESSORS
template<typename T>
size_t simple_type_descriptor<T>::sizeOf() const
{
    return sizeof(T);
}

template<typename T>
bool simple_type_descriptor<T>::has(descriptor::Flags flag) const
{
    if (flag == Flags::STRING_CAST)
        return true;

    return this->descriptor::has(flag);
}

// CAST
template<typename T>
any simple_type_descriptor<T>::cast (const any& value) const
{
    if(value.type() == this->type())
        return value ;

    std::string svalue;
    if (value.type() == typeid(std::string))
        svalue = anycast<std::string>(value);
    else
		svalue = std::move(value.desc()->atos(value));

	any destination;
	return this->stoa(svalue, destination);
}

// RAW VALUE SERIALIZATION
template<typename T>
void simple_type_descriptor<T>::set(void* ptr,const any& value) const
{
    T t ;
	if (value.desc() != this)
	{		
		t = anycast<T>(this->cast(value));
	}
	else 
		t = anycast<T>(value);

    memcpy(ptr,&t,sizeof(T));
}


template<typename T>
any& simple_type_descriptor<T>::get(void* ptr, any& value) const
{
    return value = * (T*) ptr;
}

template<typename T>
bool simple_type_descriptor<T>::equals(const any& v1, const any& v2) const
{
    return anycast<T>(v1) == anycast<T>(v2);
}

template<typename T>
any& simple_type_descriptor<T>::clear(any& value) const
{
    T t;
    return value = t;
}

template<typename T>
any simple_type_descriptor<T>::create() const
{
    T t;
    return any(t);
}

template<typename T>
std::string simple_type_descriptor<T>::atos(const any& value) const
{
    T t;
    if (value.desc() != this)
	{		
        t = anycast<T>(this->cast(value));    
	}
    else
        t = anycast<T>(value);

    return boost::lexical_cast<std::string>(t);
}



template<typename T>
any& simple_type_descriptor<T>::stoa(const std::string& string_value, any& value) const
{
    T t = boost::lexical_cast<T,std::string>(string_value);
    return value = t;
}



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif