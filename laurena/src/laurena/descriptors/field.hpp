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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          class field                                                          */ 
/*********************************************************************************/ 
class field {
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
        FLAGS_IS_BITFIELD             = 8,  // Is a bitfield (integer or boost::dynamic_biset) type
        FLAGS_IS_OWNER_SERIAL         = 9,
        FLAGS_MAX                     = 9,
    };


    /****************************************************************************/ 
    /*          callback to simulate accessors                                  */ 
    /****************************************************************************/ 

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

    void        set(any& object, const any& value)  const;
    any&        get(const any& object, any& value)        const;

    /****************************************************************************/ 
    /*              accessors                                                   */ 
    /****************************************************************************/ 

    const std::string&      name()              const;
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

    field&        isBitField(const string_array& values);
    bool                    isBitField() const;

    field&        dontArchive(bool mode);
    bool                    dontArchive() const;

    field&        ignoreIfDefaultValue(bool mode);
    bool                    ignoreIfDefaultValue() const;

    std::string&            toString(const any& object, std::string& destination) const;
    void                    fromString(any& object, const std::string& svalue) const;

	field&		setCallback(set_accessor* callback);
	field&		getCallback(get_accessor* callback);

    const any&              defaultValue () const;
    field&        defaultValue(const any&);

    
    

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    std::string                   _name;
    word32                        _offset;
    const descriptor*             _descriptor;
    boost::dynamic_bitset<>       _flags;
    const string_array*            _values;

	set_accessor*      _set_callback;
	get_accessor*	  _get_callback;

    any                           _default_value;
};

/********************************************************************************/ 
/*                                                                              */ 
/*              extension of std::vector<field>                                 */ 
/*                                                                              */ 
/********************************************************************************/
class fields : public std::vector<field>
{
public:

    fields(word8 size=0);

    const field& get(const std::string& name);
    const field* find(const std::string& name);    

    field& unused();

    protected:
    word16      _used;
 
};


/********************************************************************************/ 
/*                                                                              */ 
/*              inline function                                                 */ 
/*                                                                              */ 
/********************************************************************************/ 

inline
const std::string& field::name () const
{
    return this->_name;
}

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
void* field::ptr(void* object) const
{
    return memory::ptr(object,this->_offset);
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
field& field::setCallback(set_accessor* callback)
{
	this->_set_callback = callback;
    callback->_field = this;
	return *this;
}

inline
field& field::getCallback(get_accessor* callback)
{
	this->_get_callback = callback;
    callback->_field = this;
	return *this;
}

#define init_field(CLASSNAME,NAME,FIELD) editFields().unused().init(NAME, field_descriptor(CLASSNAME,FIELD), field_offset(CLASSNAME,FIELD)).isPointer(field_is_pointer(CLASSNAME,FIELD))

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif 