///
/// \file       field.h
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Describe a serializable field member in a class 
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable field member in a class 
///
#ifndef LAURENA_FIELD_H
#define LAURENA_FIELD_H

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

#include <laurena/memory/memory_functions.hpp>
#include <laurena/traits/laurena_traits.hpp>
#include <laurena/types/string_array.hpp>
#include <laurena/descriptors/descriptable.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          class field                                                          */ 
/*********************************************************************************/ 
class field : public descriptable {
public:

    /****************************************************************************/ 
    /*          flag values                                                     */ 
    /****************************************************************************/ 
    enum Flags {
        FLAGS_IGNORE_IF_DEFAULT_VALUE = 0,  // Don't archive it if it's default value
        FLAGS_DONT_ARCHIVE            = 1,  // Don't archive, atribute is here for internal uses
        FLAGS_IS_POINTER              = 2,  // Is a pointer type.
        FLAGS_IS_PRIMARY_KEY          = 3,  // Is a primary key (uint or string)
        FLAGS_IS_UNIQUE               = 4,  // Is unique
        FLAGS_IS_SERIAL               = 5,  // Is serial ( primary key for all serializables objects )
        FLAGS_IS_ENUM                 = 6,  // Is an enum integer type
        FLAGS_IS_BITSET               = 8,  // Is a bitset (integer or boost::dynamic_biset) type
        FLAGS_IS_OWNER_SERIAL         = 9,
		FLAGS_NO_QUOTE				  = 10, // No quote on string value. Print as it is
		FLAGS_IS_EPOCH				  = 12, // This int is an epoch (a time value in second since 1970) - or a value in seconds.
        FLAGS_MAX                     = 11,
    };


    /****************************************************************************/ 
    /*          callback to simulate accessors                                  */ 
    /****************************************************************************/ 
	typedef std::function<void(const any& obj, any& value)> getter;
	typedef std::function<void(any& obj, const any& value)> setter;

	/*
    class get_accessor 
    {
       public:

      // two possible functions to call member function. virtual cause derived
      // classes will use a pointer to an object and a pointer to a member function
      // to make the function call
      virtual void call(const any& obj, any& value) const =0 ;        // call using function

      protected:
      const field*        _field;

      friend class field;
    };

    class set_accessor 
    {
       public:

      // two possible functions to call member function. virtual cause derived
      // classes will use a pointer to an object and a pointer to a member function
      // to make the function call
      virtual void call(any& obj, const any& value) const =0 ;        // call using function

      protected:
      const field*        _field;

      friend class field;
    };
       */
        

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    field();
    field (const char* name, const descriptor* cd, word32 offset);
	~field();


    /****************************************************************************/ 
    /*                  building                                                */ 
    /****************************************************************************/ 
    field& init (const char* name, const descriptor* cd, word32 offset);
    field& init (field& source);
	field& init (const char* name, const descriptor* cd, setter setfunction, getter getfunction);

    void        set(any& object, const any& value)  const;
    any&        get(const any& object, any& value)        const;

    /****************************************************************************/ 
    /*              accessors                                                   */ 
    /****************************************************************************/ 

    const descriptor&       desc()              const;
    word32                  offset()            const;
    void*                   ptr(void* object)   const;

    bool                    isPrimaryKey ()     const;
    field&        isPrimaryKey(bool mode);

    bool                    isSerial()          const;
    field&        isSerial(bool mode);

    bool                    isOwnerSerial()     const;
    field&        isOwnerSerial(bool mode);

    bool                    isPointer()         const;
    field&        isPointer(bool mode);

    field&        isEnum(const string_array& values);
    bool                    isEnum() const;

    field&        isBitSet(const string_array& values);
    bool                    isBitSet() const;

    field&        dontArchive(bool mode);
    bool                    dontArchive() const;

    field&        ignoreIfDefaultValue(bool mode);
    bool          ignoreIfDefaultValue() const;

	field&		  noQuote(bool mode);
	bool		  noQuote() const;

    std::string&            toString(const any& object, std::string& destination) const;
    void                    fromString(any& object, const std::string& svalue) const;

	field&		hasSetter(setter callback);
	field&		hasGetter(getter callback);

    const any&              defaultValue () const;
    field&        defaultValue(const any&);

    const std::string&		supportTag() const;
	field&					supportTag(const std::string& tag);
	bool					needSupport() const;
    

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    word32                      _offset;
    const descriptor*           _descriptor;
    boost::dynamic_bitset<>     _flags;
    const string_array*         _values;

	std::string					_support_tag;

	setter						_setter;
	getter						_getter;

    any                         _default_value;
};

/********************************************************************************/ 
/*                                                                              */ 
/*              extension of std::vector<field>                                 */ 
/*                                                                              */ 
/********************************************************************************/
class fields : public std::vector<std::unique_ptr<field>>
{
public:

    fields();

    const field& get(const std::string& name)   const;
    const field* find(const std::string& name)  const;    

    field& get(const std::string& name);
    field* find(const std::string& name);    

	field&		unused();

    protected:
    word16      _used;
 
};


/********************************************************************************/ 
/*                                                                              */ 
/*              inline function for class field                                 */ 
/*                                                                              */ 
/********************************************************************************/ 

inline 
const descriptor& field::desc() const 
{ 
    return *this->_descriptor ;
}

inline 
word32 field::offset() const 
{ 
    return this->_offset ; 
}

inline
const std::string&	field::supportTag() const
{ 
	return this->_support_tag;
}

inline
field&	field::supportTag(const std::string& tag)
{
	this->_support_tag = tag;
	return *this;
}

inline
bool field::needSupport() const
{
	return this->_support_tag.length() > 0;
}

inline 
void* field::ptr(void* object) const
{
    return memory::ptr(object,this->_offset);
}

inline
field&	field::noQuote(bool mode)
{
    _flags.set(FLAGS_NO_QUOTE,mode);
    return *this;
}

inline
bool	field::noQuote() const
{
    return _flags.test(FLAGS_NO_QUOTE);
}

inline 
bool field::isPrimaryKey () const  
{ 
    return _flags.test(FLAGS_IS_PRIMARY_KEY);
}

inline field& field::isPrimaryKey(bool mode)
{
    _flags.set(FLAGS_IS_PRIMARY_KEY,mode);
    return *this;
}

inline 
bool field::isSerial()          const
{
    return _flags.test(FLAGS_IS_SERIAL);
}

inline
field&  field::isSerial(bool mode)
{
    _flags.set(FLAGS_IS_SERIAL,mode);
    return *this;
}

inline
bool field::isOwnerSerial()     const
{
    return _flags.test(FLAGS_IS_OWNER_SERIAL);
}
 
inline
field& field::isOwnerSerial(bool mode)
{
    _flags.set(FLAGS_IS_OWNER_SERIAL,mode);
    return *this;
}    

inline
bool  field::isPointer() const
{
    return _flags.test(FLAGS_IS_POINTER);  
}

inline
field&  field::isPointer(bool mode)
{
    this->_flags.set(FLAGS_IS_POINTER,mode);
    return *this;
}

inline
bool  field::dontArchive() const
{
    return _flags.test(FLAGS_DONT_ARCHIVE);  
}

inline
field& field::ignoreIfDefaultValue(bool mode)
{
    this->_flags.set(FLAGS_IGNORE_IF_DEFAULT_VALUE);
    return *this;
}

inline
bool field::ignoreIfDefaultValue() const
{
    return _flags.test(FLAGS_IGNORE_IF_DEFAULT_VALUE);
}


inline
const any& field::defaultValue () const
{
    return this->_default_value;
}

inline 
field&  field::defaultValue(const any& value)
{
    this->_default_value = value;
    return *this;
}

inline
field& field::dontArchive(bool mode)
{
    this->_flags.set(FLAGS_DONT_ARCHIVE,mode);
    return *this;
}


inline
field& field::hasSetter(setter callback)
{
	this->_setter = callback;
	return *this;
}

inline
field& field::hasGetter(getter callback)
{
	this->_getter = callback;
	return *this;
}
 
//#define init_field(CLASSNAME,NAME,FIELD)	editFields().unused().init(NAME, field_descriptor(CLASSNAME,FIELD), offsetof(CLASSNAME,FIELD)).isPointer(field_is_pointer(CLASSNAME,FIELD))
//#define init_virtual_field(NAME,FIELDCLASS,SETTER,GETTER)    editFields().unused().init(NAME,classes::byType(typeid(FIELDCLASS)),SETTER,GETTER)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif 