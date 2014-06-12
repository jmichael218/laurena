///
/// \file     numeric_type_descriptors.hpp
/// \brief    int and other number types descriptor template
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// int and other number types descriptor template
///

#ifndef LAURENA_NUMERIC_TYPE_DESCRIPTOR_H
#define LAURENA_NUMERIC_TYPE_DESCRIPTOR_H

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

#include <laurena/descriptors/classes.hpp>
#include <laurena/descriptors/simple_type_descriptor.hpp>

#include <laurena/casting/lexical_cast.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


template<typename T>
class numeric_type_descriptor : public simple_type_descriptor<T>
{
public:
    
    // CONSTRUCTOR
    numeric_type_descriptor(const char* name) : simple_type_descriptor<T>(name) {}
    
    // ACCESSORS
    virtual bool    has(descriptor::Flags flag) const 
    {
        return (flag == descriptor::Flags::NUMERIC_VALUE || flag == descriptor::Flags::ATOMIC) ? 
			true : 
			this->simple_type_descriptor<T>::has(flag) ;
    }

    virtual std::string atos(const any& value) const
    {
        T t;
        if (value.desc() != this)
	    {		
            t = anycast<T>(this->cast(value));    
	    }
        else
            t = anycast<T>(value);

        return lexical_cast<std::string>(t);
    }

    virtual any& stoa(const std::string& string_value, any& value) const
    {
        T t = lexical_cast<T,std::string>(string_value);
        return value = t;
    }
};




/*********************************************************************************/
/*          word8 type  descriptor                                               */ 
/*********************************************************************************/ 

class word8_type_descriptor : public numeric_type_descriptor<word8>
{
public:

    // CONSTRUCTOR
    word8_type_descriptor ();

    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
	virtual any&            stoa(const std::string& string_value, any& value) const;        
};

template<> 
struct td<word8>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new word8_type_descriptor();
            classes::add(res);
        }
        return res;
    }
};


/********************************************************************************/
/*          int8 type descriptor                                                */ 
/********************************************************************************/ 
class int8_type_descriptor : public numeric_type_descriptor<int8>
{
public:

    // CONSTRUCTOR
    int8_type_descriptor ();

    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
	virtual any&            stoa(const std::string& string_value, any& value) const;         
};

template<> 
struct td<int8>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new int8_type_descriptor();
            classes::add(res);
        }
        return res;
    }
};

/*********************************************************************************/
/*          word16 type  descriptor                                              */ 
/*********************************************************************************/ 

template<> 
struct td<word16>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<word16>("word16");
            classes::add(res);
        }
        return res;
    }
};

/********************************************************************************/
/*          int16 type descriptor                                               */ 
/********************************************************************************/ 
template<> 
struct td<int16>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<int16>("int16");
            classes::add(res);
        }
        return res;
    }
};

/*********************************************************************************/
/*          word32 type  descriptor                                              */ 
/*********************************************************************************/ 

template<> 
struct td<word32>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<word32>("word32");
            classes::add(res);
        }
        return res;
    }
};

/********************************************************************************/
/*          int32 type descriptor                                               */ 
/********************************************************************************/ 
template<> 
struct td<int32>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<int32>("int32");
            classes::add(res);
        }
        return res;
    }
};

/*********************************************************************************/
/*          word64 type  descriptor                                              */ 
/*********************************************************************************/ 

template<> 
struct td<word64>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<word64>("word64");
            classes::add(res);
        }
        return res;
    }
};

/********************************************************************************/
/*          int64 type descriptor                                               */ 
/********************************************************************************/ 
template<> 
struct td<int64>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            
            res=new numeric_type_descriptor<int64>("int64");
            classes::add(res);
        }
        return res;
    }
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif