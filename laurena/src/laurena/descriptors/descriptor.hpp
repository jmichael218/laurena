///
/// \file       descriptor.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Describe a serializable type
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable type
///
#ifndef LAURENA_DESCRIPTOR_H
#define LAURENA_DESCRIPTOR_H

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

#include <laurena/descriptors/features/class_features.hpp>
#include <laurena/descriptors/annotation.hpp>
#include <laurena/descriptors/descriptable.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/********************************************************************************/ 
/*              forward declaration                                             */ 
/********************************************************************************/ 

class method_descriptor;
class method_table;
class class_feature;
class any;
class field;
class fields;

/*********************************************************************************/
/*          descriptor                                                           */ 
/*********************************************************************************/ 
class descriptor : public descriptable {

	/****************************************************************************/
	/*			enum for flags												    */ 
	/****************************************************************************/ 
	public:
	enum class Flags  {
		NUMERIC_VALUE 	//<! The descriptor type is a numeric value (int, char, float .... )
		,PRIMARY_KEY 	//<! The class does have a member field acting as a primary key i.e : identifying a unique object in a collection through this value
		,SERIAL			//<! The class does have a member field acting as a serial i.e  : identifying the object among all object of any class having also a serial key
		,FIELDS			//<! The class does have member fields
		,METHODS		//<! The descriptor does have description of methods and can execute them by name finding i.e the class can be used in an interpreted language
		,STRING_CAST    //<! The type can be printed as a string, like int i = 1 => has a string casted value of "1" ;
		,ATOMIC			//<! atomic type are numeric value or std::string , no fields, can pass copy value instead of pointer or reference
		,NO_QUOTE		//<! A string value but don't display quote (like boolean as true or false instead of "true" or "false"


	};

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    public:
    //! Constructor    
    /*! This is the only constructor available. Name and type can't be changed over the descriptor lifetime.    
        \param name The identifier name of the class. It must be unique.
        \param type A reference to the type_info of the class.
    */    
    descriptor(const char* name,const type_info& type);    

    //! Destructor
    /*! This is the class destructor. It delete method wrappers if any have been declared. */
    virtual ~descriptor();
    
    /****************************************************************************/ 
    /*          getters                                                         */ 
    /****************************************************************************/ 

    //! Return type_info structure of the class described.
    inline const type_info&   type() const { return _type; }

	//! Return true if the class support a given class flag
	virtual bool has(Flags flag) const;
   
    /****************************************************************************/
    /*          OPERATORS                                                       */ 
    /****************************************************************************/

	//! Return true if a0 and a1 must be considered as equals.
    virtual bool equals(const any& a0, const any& a1) const;

    /****************************************************************************/ 
    /*          POLYMORPHISM                                                    */ 
    /****************************************************************************/ 

	//! Return the true descriptor of a polymorphic object.
	/*! Example: class A {} ; class B : A {} ; A* ptr = new B() ; Adescriptor->resolve (ptr); should return B's descriptor. */
    virtual const descriptor& resolve(const any& value) const;
    
    /****************************************************************************/ 
    /*          FEATURES                                                        */ 
    /****************************************************************************/ 

	//! Return a pointer to the requested feature, or nullptr if not this feature supported by this class.	
    virtual const class_feature* feature(Feature featureId) const;

	//! Return true if the requested feature is supported, i.e : this->feature(featureId) will return a non-null pointer.
    virtual bool hasFeature(Feature featureId) const;
   
    /****************************************************************************/ 
    /*                                                                          */ 
    /*              ACCESSORS                                                   */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Return size for static sized pod objects like int, float, ...
    virtual size_t size_of() const;

    //! Set default value, when defined
    virtual any& clear(any& value) const;

    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  CAST                                                    */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Try to convert the type of the parameter to the descriptor's type. 	
	/*! Try to convert the parameter into the descriptor's type. 
		Example std::string a = "1"; int i = td<int>::desc()->cast(a); 
	*/
    virtual any cast (const any& value) const;


    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  FUNCTIONS ON PRIMARY KEYS                               */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Get the field descriptor of the primary key. Raises exception if the class doesn't have a primary key defined.   
    virtual const field& primaryKey() const;

    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  FUNCTIONS ON SERIAL                                     */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Get the field descriptor of the serial key field. Raises exception if the class doesn't have a serial field member defined.
    virtual const field& serial() const;


    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  RAW VALUE SERIALIZATION                                 */ 
    /*                                                                          */ 
    /****************************************************************************/ 
    //! unserialize a value into memory
    ///
    ///    
    /// param ptr : a pointer to the value. For example if the value is an int, ptr is an int* i.e int* pint = (int*) ptr
    /// param any : hold the value to set    
    virtual void set(void* ptr, const any& value) const;

    //! serialize a value into memory
    virtual any& get(void* ptr, any& value) const;

    /****************************************************************************/ 
    /*                                                                          */ 
    /*          FIELD MEMBER FUNCTIONS                                          */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Return attributes if any, raise exception if hasAttributes() return false. Doesn't return fields of the parent class.    
    virtual const fields& get_fields() const;

	//! Return a pointer to the requested field, nullptr if not exist
	virtual const field* findField(const std::string& field_name) const;

    //! Return a reference to the requested field, raise an UnimplementedException exception if not exist
    virtual const field& getField(const std::string& field_name) const;


    //! Set a field member value
    void setObjectField(any& object,const std::string& field, const any& value) const;
    
    template<class T>
    inline void setObjectField(T* object, const std::string& field, const any& value) const
    { 
		any a = object;
		this->setObjectField (a,field,value) ; 
	}

    //! Read a field member value   
    virtual any& getFieldValue(const any& ptr, const std::string& attribute_name,any& value) const;

    template<class T>
    inline any& getFieldValue(const T* object, const std::string& field, any& value) const
    { 
		any a = object;
		return this->getFieldValue (a,field,value) ; 
	}

    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  METHODS                                                 */ 
    /*                                                                          */ 
    /****************************************************************************/ 
    const method_descriptor* method(const std::string& method_name) const;
    const method_descriptor* method(const char* method_name)        const;

    void method(method_descriptor* method);

    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  TO/FROM STRING SERIALIZATION                            */ 
    /*                                                                          */ 
    /****************************************************************************/ 

    //! Serialization to a string     
	//! atos = Any TO String
    virtual std::string atos(const any& value) const;

    //! Unserialization from string    
	//! stoa = String To Any
	virtual any& stoa(const std::string& string_value, any& ) const;


    /****************************************************************************/ 
    /*                                                                          */ 
    /*                  OBJECT CONSTRUCTOR FOR INJECTION                        */ 
    /*                                                                          */ 
    /****************************************************************************/ 
    //! Call default constructor of the described class
    virtual any create() const;

	/****************************************************************************/
	/*																			*/
	/*					ANNOTATIONS												*/ 
	/*																			*/ 
	/****************************************************************************/ 

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    const std::type_info&           _type;		/*!< type_info of the class		*/    
    method_table*					_methods;	/*!< array of class methods		*/ 
	
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif