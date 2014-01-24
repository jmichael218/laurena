///
/// \file     enum_descriptor.hpp
/// \brief    Describe an enum type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe an enum type
///

#ifndef LAURENA_ENUM_DESCRIPTOR_H
#define LAURENA_ENUM_DESCRIPTOR_H

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

#include <laurena/exceptions/failed_parsing_exception.hpp>
#include <laurena/descriptors/simple_type_descriptor.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/ 
/*          enum_descriptor                                                      */ 
/*********************************************************************************/
template<typename T>
class enum_type_descriptor : public simple_type_descriptor<T>
{
public:
    
    // CONSTRUCTOR
    enum_type_descriptor(const char* name, const string_array& values);
    
    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 
    // ACCESSORS
    virtual bool    has(descriptor::Flags flag) const;


    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
    virtual any&            stoa(const std::string& string_value, any& value) const;
    /*
    virtual std::string     atos(const any& value) const
    {
        T t = anycast<T>(value);
        return this->_values[t];
    }
	virtual any&            stoa(const std::string& string_value, any& value) const
    {
        int i = this->_values.find(string_value);
        if (i==-1)        
            throw LAURENA_FAILED_PARSING_EXCEPTION("In enum_type_descript::stoa, failed to convert the string value",string_value);
        
        return value = (T) i;
    }
    */
    /****************************************************************************/
    /*          static functions                                                */ 
    /****************************************************************************/ 
    public:
    static enum_type_descriptor<T>* build(const char* name, const string_array& values)
	{
        enum_type_descriptor<T>* cd = new enum_type_descriptor<T>(name, values);
        classes::add(cd);        
        return cd;
    } 


    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 


protected:

	const string_array&		_values;
};

/********************************************************************************/ 
/*          templated code                                                      */ 
/********************************************************************************/ 

// CONSTRUCTOR
template<typename T>
enum_type_descriptor<T>::enum_type_descriptor (const char* name, const string_array& values) : simple_type_descriptor(name), _values(values)
{ }

// ACCESSORS
template<typename T>
bool enum_type_descriptor<T>::has(descriptor::Flags flag) const
{
	    if (flag == descriptor::Flags::STRING_CAST)
		    return true;
	    if (flag == descriptor::Flags::TINY)
		    return true;
        if (flag == descriptor::Flags::NUMERIC_VALUE)
            return true;
	    return this->descriptor::has(flag) ;
}

// TO/FROM STRING SERIALIZATION 
template<typename T>
std::string enum_type_descriptor<T>::atos(const any& value) const
{
    T t = anycast<T>(value);
    return this->_values[t];
}

template<typename T>
any& enum_type_descriptor<T>::stoa(const std::string& string_value, any& value) const
{
    int i = this->_values.find(string_value);
    if (i==-1)        
        throw LAURENA_FAILED_PARSING_EXCEPTION("In enum_type_descript::stoa, failed to convert the string value",string_value);
        
    return value = (T) i;
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif