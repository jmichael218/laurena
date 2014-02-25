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
#include <laurena/exceptions/class_not_found_exception.hpp>

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
    /*          const        ants                                               */ 
    /****************************************************************************/ 
    static const word16 FIELD_UNDEFINED;

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    base_standard_class_descriptor(const char* name, const type_info& type, size_t sizeOfObject, const descriptor* parent = nullptr);
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
        
    base_standard_class_descriptor& primaryKeyField(const std::string& fieldName);
    base_standard_class_descriptor& serialKeyField (const std::string& fieldName);

    inline fields& editFields() { return _fields ; }


    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    fields        _fields;
    
    size_t        _primary_key_field;
    size_t        _serial_field;

};

template<typename T>
class standard_class_descriptor : public base_standard_class_descriptor
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
	standard_class_descriptor(const char* name, const descriptor* parent = nullptr)
		: base_standard_class_descriptor(name,typeid(T),sizeof(T),parent)
	{
	}

    /****************************************************************************/ 
    /*          field edition							                        */ 
    /****************************************************************************/ 
	template<typename FIELDTYPE>
	inline field& addField(FIELDTYPE T::*f, const char* name)
	{
		typedef typename traits<FIELDTYPE>::basetype basetype;
		const descriptor* fdesc = classes::byType(typeid(basetype));
        if (!fdesc)
        {
            throw LAURENA_CLASS_NOT_FOUND_EXCEPTION(typeid(basetype), "Unresolved field type");
        }
		word32 offset = (word32) &(((T*)(0))->*f);
		bool bIsPointer = std::is_pointer<FIELDTYPE>::value;
		return this->editFields().unused().init(name, fdesc, offset).isPointer(bIsPointer);
	}

	template<typename FIELDTYPE>
	inline field& addField(const char* name, field::setter setter, field::getter getter)
	{
		typedef typename traits<FIELDTYPE>::basetype basetype;
		const descriptor* fdesc = classes::byType(typeid(basetype));
        if (!fdesc)
        {
            throw LAURENA_CLASS_NOT_FOUND_EXCEPTION(typeid(basetype), "Unresolved field type");
        }
		bool bIsPointer = std::is_pointer<FIELDTYPE>::value;
		return this->editFields().unused().init(name, fdesc, setter, getter);
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

	virtual any create() const
	{
		if(_constructor)
		{
			return any((T*) _constructor());
		}
		else
		{
			std::string message = "class constructor not set for descriptor ";
			message.append (this->name());
			
			throw LAURENA_NULL_POINTER_EXCEPTION(message);
		}
	}

    virtual any cast (const any& value) const
    {       
        return any(anycast<T*>(value));
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
    static standard_class_descriptor<T>* build(const char* name, const descriptor* parentClassDescriptor=nullptr)
	{
        standard_class_descriptor<T>* cd = new standard_class_descriptor<T>(name, parentClassDescriptor);
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