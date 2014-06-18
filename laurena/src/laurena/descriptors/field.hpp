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
    enum Flags : unsigned char 
    {
        FLAGS_IGNORE_IF_DEFAULT_VALUE = 0,  // Don't archive it if it's default value
        FLAGS_DONT_ARCHIVE            = 1,  // Don't archive, atribute is here for internal uses
        FLAGS_IS_POINTER              = 2,  // Is a pointer type.
        FLAGS_IS_PRIMARY_KEY          = 3,  // Is a primary key (uint or string)
        FLAGS_IS_UNIQUE               = 4,  // Is unique
        FLAGS_IS_SERIAL               = 5,  // Is serial ( primary key for all serializables objects )
        FLAGS_IS_SHARED_POINTER       = 6,

		// 6, 7, 8 unused
        FLAGS_IS_OWNER_SERIAL         = 9,
		FLAGS_NO_QUOTE				  = 10, // No quote on string value. Print as it is

        FLAGS_MAX                     = 11,
    };


    /****************************************************************************/ 
    /*          callback to simulate accessors                                  */ 
    /****************************************************************************/ 
	typedef std::function<void(const any& obj, any& value)> getter;
	typedef std::function<void(any& obj, const any& value)> setter;

        
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

    bool          is_primary_key ()     const;
    field&        is_primary_key(bool mode);

    bool          is_serial()          const;
    field&        is_serial(bool mode);

    bool          is_owner_serial()     const;
    field&        is_owner_serial(bool mode);

    bool          is_pointer()         const;
    field&        is_pointer(bool mode);

    bool          is_shared_pointer()  const;
    field&        is_shared_pointer(bool mode);

    field&        dont_archive(bool mode);
    bool          dont_archive() const;

    field&        ignore_if_default_value(bool mode);
    bool          ignore_if_default_value() const;

	field&		  no_quote(bool mode);
	bool		  no_quote() const;

    std::string&   tos(const any& object, std::string& destination) const;
    void           froms(any& object, const std::string& svalue) const;

	field&		   set_callback(setter callback);
	field&		   get_callback(getter callback);

    const any&    default_value () const;
    field&        default_value(const any&);



    const std::string&		support_tag() const;
	field&					support_tag(const std::string& tag);
	bool					need_support() const;
    

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    word32                      _offset;
    const descriptor*           _descriptor;
    std::bitset<FLAGS_MAX>      _flags;
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

    int           index(const std::string& name) const;

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
const std::string&	field::support_tag() const
{ 
	return this->_support_tag;
}

inline
field&	field::support_tag(const std::string& tag)
{
	this->_support_tag = tag;
	return *this;
}

inline
bool field::need_support() const
{
	return this->_support_tag.length() > 0;
}

inline 
void* field::ptr(void* object) const
{
    return memory::ptr(object,this->_offset);
}

inline
field&	field::no_quote(bool mode)
{
    _flags.set(FLAGS_NO_QUOTE,mode);
    return *this;
}

inline
bool	field::no_quote() const
{
    return _flags.test(FLAGS_NO_QUOTE);
}

inline 
bool field::is_primary_key () const  
{ 
    return _flags.test(FLAGS_IS_PRIMARY_KEY);
}

inline field& field::is_primary_key(bool mode)
{
    _flags.set(FLAGS_IS_PRIMARY_KEY,mode);
    return *this;
}

inline 
bool field::is_serial()          const
{
    return _flags.test(FLAGS_IS_SERIAL);
}

inline
field&  field::is_serial(bool mode)
{
    _flags.set(FLAGS_IS_SERIAL,mode);
    return *this;
}

inline
bool field::is_owner_serial()     const
{
    return _flags.test(FLAGS_IS_OWNER_SERIAL);
}
 
inline
field& field::is_owner_serial(bool mode)
{
    _flags.set(FLAGS_IS_OWNER_SERIAL,mode);
    return *this;
}    

inline
bool  field::is_pointer() const
{
    return _flags.test(FLAGS_IS_POINTER);  
}

inline
field&  field::is_pointer(bool mode)
{
    this->_flags.set(FLAGS_IS_POINTER,mode);
    return *this;
}

inline
bool  field::is_shared_pointer()  const
{
    return this->_flags.test(FLAGS_IS_SHARED_POINTER);
}

inline
field& field::is_shared_pointer(bool mode)
{
    this->_flags.set(FLAGS_IS_SHARED_POINTER, mode);
    return *this;
}

inline
bool  field::dont_archive() const
{
    return _flags.test(FLAGS_DONT_ARCHIVE);  
}

inline
field& field::ignore_if_default_value(bool mode)
{
    this->_flags.set(FLAGS_IGNORE_IF_DEFAULT_VALUE);
    return *this;
}

inline
bool field::ignore_if_default_value() const
{
    return _flags.test(FLAGS_IGNORE_IF_DEFAULT_VALUE);
}


inline
const any& field::default_value () const
{
    return this->_default_value;
}

inline 
field&  field::default_value(const any& value)
{
    this->_default_value = value;
    return *this;
}

inline
field& field::dont_archive(bool mode)
{
    this->_flags.set(FLAGS_DONT_ARCHIVE,mode);
    return *this;
}


inline
field& field::set_callback(setter callback)
{
	this->_setter = callback;
	return *this;
}

inline
field& field::get_callback(getter callback)
{
	this->_getter = callback;
	return *this;
}
 
//#define init_field(CLASSNAME,NAME,FIELD)	editFields().unused().init(NAME, field_descriptor(CLASSNAME,FIELD), offsetof(CLASSNAME,FIELD)).isPointer(field_is_pointer(CLASSNAME,FIELD))
//#define init_virtual_field(NAME,FIELDCLASS,SETTER,GETTER)    editFields().unused().init(NAME,classes::by_type(typeid(FIELDCLASS)),SETTER,GETTER)

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif 