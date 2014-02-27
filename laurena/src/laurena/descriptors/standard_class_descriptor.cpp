///
/// \file     standard_class_descriptor.hpp
/// \brief    Describe a serializable class composed of serializable fields 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable class composed of serializable fields 
///

#include <laurena/descriptors/standard_class_descriptor.hpp>

using namespace laurena;

const word16 base_standard_class_descriptor::FIELD_UNDEFINED = 0xFFFF;

base_standard_class_descriptor::base_standard_class_descriptor(const char* name, const type_info& type, size_t sizeOfObject, const descriptor* parent) :

    polymorphic_class_descriptor(name, type, sizeOfObject, parent) ,
    _fields(), _primary_key_field(FIELD_UNDEFINED), _serial_field(FIELD_UNDEFINED)

{ 
    _size_of = sizeOfObject;
}

base_standard_class_descriptor::~base_standard_class_descriptor ()
{ }

/********************************************************************************/ 
/*																				*/ 
/*				ACCESSORS														*/ 
/*																				*/ 
/********************************************************************************/ 
bool base_standard_class_descriptor::has(descriptor::Flags flag) const
{
	switch(flag)
	{
		case Flags::PRIMARY_KEY:
			return ( this->_primary_key_field != FIELD_UNDEFINED ) ?
				true :
				( this->hasParent() ? this->parent().has(Flags::PRIMARY_KEY) : false );

		case Flags::SERIAL:
            return ( this->_serial_field != FIELD_UNDEFINED ) ?
                true :
                ( this->hasParent() ? this->parent().has(Flags::SERIAL) : false );

        case Flags::FIELDS:
            return (this->_fields.size() > 0) ? 
                true :
                ( this->hasParent() ? this->parent().has(Flags::FIELDS) : false ) ;
		default:
			return this->polymorphic_class_descriptor::has(flag);
	}
}

/********************************************************************************/ 
/*                                                                              */ 
/*              FUNCTIONS ON PRIMARY KEYS                                       */ 
/*                                                                              */ 
/********************************************************************************/ 
const field&  base_standard_class_descriptor::primaryKey() const
{   
    if (this->_primary_key_field >= this->_fields.size())
    {
        if (this->hasParent())
            return this->parent().primaryKey();

        std::string message = "Class ";
        message.append(this->name()).append (" doesn't have any primary key defined.");        
        throw LAURENA_NULL_POINTER_EXCEPTION(message);
    }
    else
        return *this->_fields[this->_primary_key_field];
}

const field& base_standard_class_descriptor::serial() const
{
    if (this->_serial_field >= this->_fields.size())
    {
        if (this->hasParent())
            return this->parent().serial();

        std::string message = "Class ";
        message.append(this->name()).append (" doesn't have any serial key defined.");        
        throw LAURENA_NULL_POINTER_EXCEPTION(message);
    }
    else
        return *this->_fields[this->_serial_field];
}

/********************************************************************************/ 
/*                                                                              */ 
/*              FIELD MEMBER FUNCTIONS                                          */ 
/*                                                                              */ 
/********************************************************************************/ 

const field& base_standard_class_descriptor::getField(const std::string& field_name) const
{
    for (const std::unique_ptr<field>& f : this->_fields)
    {
        if (f->name() == field_name)
            return *f;
    }

    if (!this->hasParent())
    {
        std::string message (field_name);
        message.append("' is an unknow field member");
        throw LAURENA_NULL_POINTER_EXCEPTION(message.c_str());
    }
    else
        return this->parent().getField(field_name);

}

const field* base_standard_class_descriptor::findField(const std::string& field_name) const
{
    for (const std::unique_ptr<field>& f : this->_fields)
    {
        if (f->name() == field_name)
            return f.get();
    }

	if (this->hasParent() == false)
		return nullptr;
    else
        return this->parent().findField(field_name);

}

const fields& base_standard_class_descriptor::getFields() const
{
    return this->_fields;
}

/********************************************************************************/ 
/*                                                                              */ 
/*              NEW FUNCTIONS                                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
base_standard_class_descriptor& base_standard_class_descriptor::primary_key(const std::string& fieldName)
{
    int index = this->_fields.index(fieldName);
    if (index != FIELD_UNDEFINED)
    {
        this->_fields[index]->isPrimaryKey(true);
        this->_primary_key_field = index;   
        return *this;

        std::string s = "Field ";
        s.append(fieldName).append(" not found in class ").append(this->name());
        throw LAURENA_EXCEPTION(s);
    }  
    return *this;
}

base_standard_class_descriptor& base_standard_class_descriptor::serial_key(const std::string& fieldName)
{
    int index = this->_fields.index(fieldName);
    if (index != FIELD_UNDEFINED)
    {
        this->_fields[index]->isSerial(true);
        this->_serial_field = index;   
        return *this;

        std::string s = "Field ";
        s.append(fieldName).append(" not found in class ").append(this->name());
        throw LAURENA_EXCEPTION(s);
    }  
    return *this;
}


//End of file
