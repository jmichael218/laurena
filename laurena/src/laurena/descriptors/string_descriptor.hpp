///
/// \file     string_descriptor.hpp
/// \brief    A special class descriptor for std::string
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A special class descriptor for std::string
///

#ifndef LAURENA_CORE_STRING_CLASS_DESCRIPTOR_H
#define LAURENA_CORE_STRING_CLASS_DESCRIPTOR_H

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
#include <laurena/types/any.hpp>
#include <laurena/traits/laurena_traits.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          ClassDescriptor                                                      */ 
/*********************************************************************************/ 
class string_descriptor : public descriptor {
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    string_descriptor();


    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 

	//ACCESSORS
	virtual any& clear(any& value) const;
	virtual bool has(descriptor::Flags flag) const;

	//CAST
	virtual any cast (const any& value) const;

	// OPERATORS
	virtual bool equals(const any& a0, const any& a1) const;

    // RAW VALUE SERIALIZATION
    virtual void            set(void* ptr, const any& value)  const;
    virtual any&            get(void* ptr, any& value)  const;

    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
	virtual any&            stoa(const std::string& string_value, any& value) const;    
    
    // OBJECT CONSTRUCTOR FOR INJECTION 
    virtual any create() const;



};

template<> 
struct td<std::string>
{
    static const descriptor* desc()
    {
        static descriptor* res = NULL;

        if (res == NULL)
        {
            res = new string_descriptor();
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