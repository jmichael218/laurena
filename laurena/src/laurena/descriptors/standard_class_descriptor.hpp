///
/// \file     standard_class_descriptor.hpp
/// \brief    Describe a serializable class composed of serializable fields 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable class composed of serializable fields 
///

#ifndef LAURENA_STANDARD_CLASS_DESCRIPTOR_H
#define LAURENA_STANDARD_CLASS_DESCRIPTOR_H

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
#include <laurena/descriptors/polymorphic_class_descriptor.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/descriptors/method_descriptor.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          base_standard_class_descriptor                                       */ 
/*********************************************************************************/ 

class base_standard_class_descriptor : public polymorphic_class_descriptor {
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    base_standard_class_descriptor(const char* name, const type_info& type, size_t sizeOfObject, word8 nbAttributes =0, const descriptor* parent = nullptr);
    virtual ~base_standard_class_descriptor();


    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 

    // ACCESSORS  
	virtual bool has(descriptor::Flags flag) const;

    // PARENT CLASS ACCESSORS

     // FUNCTIONS ON PRIMARY KEYS
    virtual const field&            primaryKey() const;
    virtual const field&            serial() const;

    /****************************************************************************/ 
    /*                                                                          */ 
    /*          FIELD MEMBER FUNCTIONS                                          */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    ///
    /// \brief Return attributes if any, raise exception if hasAttributes() return false
    ///
    /// Doesn't return fields of the parent class.
    ///
    virtual const fields& getFields() const;

	virtual const field* findField(const std::string& field_name) const;

    ///
    /// \brief get a reference to a field.
    ///
    /// param field_name : name of the searched field.
    /// return a reference to the field
    /// throw UnimplementedException when descriptor is a type without field ( an int for example )
    virtual const field& getField(const std::string& field_name) const;

    // TO/FROM STRING SERIALIZATION 
    
    //  BINARY SERIALIZATION  

    // OBJECT CONSTRUCTOR FOR INJECTION 
    // OBJECT CONSTRUCTOR FOR INJECTION 

    

    /****************************************************************************/ 
    /*          new functions                                                   */ 
    /****************************************************************************/ 
        
    base_standard_class_descriptor& primaryKeyField(word8 index);
    base_standard_class_descriptor& serialKeyField (word8 index);

    inline fields& editFields() { return _fields ; }


    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    fields        _fields;
    
    word8         _primary_key_field;
    word8         _serial_field;

};

template<typename T>
class standard_class_descriptor : public base_standard_class_descriptor
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
	standard_class_descriptor(const char* name, word8 nb_attributes = 0, const descriptor* parent = nullptr)
		: base_standard_class_descriptor(name,typeid(T),sizeof(T),nb_attributes,parent)
	{
	}


    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 



	//  RAW VALUE SERIALIZATION
	virtual any& get(void* ptr, any& value) const
	{
        T* t = (T*) ptr;
        const descriptor& cd = this->resolve(t);
        if (&cd == this)
            value = t;
        else 
            cd.get(ptr,value);

		return value;
	}

    virtual void set(void* ptr, const any& value) const
    {
        T* v = anycast<T*>(value);
        T* dest = (T*) ptr;
        *dest = *v;
    }

    virtual any& clear(any& value) const 
    {
        T t ;
        value  = t;
        return value;
    
    }

	virtual any& create(any& destination) const
	{
		if(_constructor)
		{
			T* t = (T*) _constructor();
			destination = t;
			return destination;
		}
		else
		{
			throw LAURENA_NULL_POINTER_EXCEPTION("In PolymorphicClassDescriptor::constructor(), class constructor not set.");
		}
	}

    virtual any& cast (any& value) const
    {
        T* t = anycast<T*>(value);
        value = t;
        return value;
    }

    inline void constructor (std::function<T* ()> constructor) { this->_constructor = constructor ; }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    std::function<T* ()>        _constructor;

    /****************************************************************************/
    /*          static functions                                                */ 
    /****************************************************************************/ 
    public:
    static standard_class_descriptor<T>* build(const char* name, const descriptor* parentClassDescriptor=nullptr, word8 nbFields =0)
	{
        standard_class_descriptor<T>* cd = new standard_class_descriptor<T>(name,nbFields, parentClassDescriptor);
        cd->constructor([](){return new T;});
        classes::add(cd);        
        return cd;
    } 

   

};

#define class_descriptor(TYPENAME,NAME) standard_descriptor<TYPENAME>::build(NAME)
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif