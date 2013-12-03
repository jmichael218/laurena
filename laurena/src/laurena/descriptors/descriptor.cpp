///
/// \file       descriptor.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      Describe a serializable type
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable type
///
#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/descriptors/method_descriptor.hpp>
#include <laurena/exceptions/unimplemented_exception.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*              CONSTRUCTOR , DESTRUCTORS                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

descriptor::descriptor(const char* name, const type_info& type) : descriptable (name), _type (type), _methods (nullptr) 
{
}

descriptor::~descriptor()
{
    if ( this->_methods)
    {
        delete this->_methods;
        this->_methods = nullptr;
    }
}


const class_feature* descriptor::feature(Feature featureId) const
{
    return nullptr;
}

bool descriptor::hasFeature(Feature featureId) const
{
    return this->feature(featureId) != nullptr;
}

/********************************************************************************/
/*                                                                              */ 
/*              OPERATORS                                                       */ 
/*                                                                              */ 
/********************************************************************************/ 
bool descriptor::equals(const any& a0, const any& a1) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("equals not implemented for this class");
}

/********************************************************************************/ 
/*                                                                              */ 
/*              POLYMORPHISM                                                    */ 
/*                                                                              */ 
/********************************************************************************/ 
const descriptor& descriptor::resolve(const any& value) const
{
    return *this;
}

/********************************************************************************/ 
/*                                                                              */ 
/*              ACCESSORS                                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

size_t descriptor::sizeOf() const 
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("sizeOf not implemented for this class");
}

any descriptor::cast (const any& value) const
{
    if (value.type() == this->type())
    {
        return any(value);
    }
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("recast not implemented for this class");
}

any& descriptor::clear(any& value) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("init not implemented for this class");
}

bool descriptor::has(descriptor::Flags flag) const
{
    return false;
}
/********************************************************************************/ 
/*                                                                              */ 
/*              PRIMARY KEY FUNCTIONS                                           */ 
/*                                                                              */ 
/********************************************************************************/ 

const field& descriptor::primaryKey() const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class doesn't have a primary key.");
}

const field& descriptor::serial() const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class doesn't have a serial key.");
}

/********************************************************************************/ 
/*                                                                              */ 
/*              RAW VALUE SERIALIZATION                                         */ 
/*                                                                              */ 
/********************************************************************************/ 
void descriptor::set(void* ptr, const any& value) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("set operation is not implemented for this class.");
}
any& descriptor::get(void* ptr, any& value) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("get operation is not implemented for this class.");
}

/********************************************************************************/ 
/*                                                                              */ 
/*              FIELD MEMBERS ACCESSORS                                         */ 
/*                                                                              */ 
/********************************************************************************/ 

const field* descriptor::findField(const std::string& field_name) const
{
	return nullptr;
}

const field& descriptor::getField(const std::string& field_name) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class doesn't have field members.");
}


const fields& descriptor::getFields() const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class doesn't have field members.");
}


void descriptor::setObjectField(any& object,const std::string& field_name, const any& value) const
{
    const field& f = this->getField(field_name);
    f.set(object,value);
}

any& descriptor::getFieldValue(const any& ptr, const std::string& field_name, any& value) const
{
    const field& f = this->getField(field_name);
    return f.get(ptr,value);    
}

/********************************************************************************/ 
/*                                                                              */ 
/*              TO STRING SERIALIZATION                                         */ 
/*                                                                              */ 
/********************************************************************************/ 
std::string descriptor::atos(const any& value) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class is not serializable to string.");    
}

any& descriptor::stoa(const std::string& string_value, any& value) const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class is not serializable from string.");    

}


/********************************************************************************/ 
/*                                                                              */ 
/*              OBJECT CREATION                                                 */ 
/*                                                                              */ 
/********************************************************************************/ 
any descriptor::create() const
{
    throw new LAURENA_UNIMPLEMENTED_EXCEPTION("this class doesn't have a declared constructor.");
}

/********************************************************************************/ 
/*                                                                              */ 
/*              METHODS                                                         */ 
/*                                                                              */ 
/********************************************************************************/ 
const method_descriptor* descriptor::method(const std::string& method_name) const
{
    if (!this->_methods)
        return nullptr ;
    return this->_methods->find(method_name)->second;

}

const method_descriptor* descriptor::method(const char* method_name) const
{
    if (!this->_methods)
        return nullptr ;
    std::string sname = method_name;
    return this->_methods->find(sname)->second;
}

void descriptor::method(method_descriptor* method)
{
    if ( this->_methods == nullptr)
        this->_methods = new method_table ();

    this->_methods->operator[] (method->name()) = method;
}


//End of file
