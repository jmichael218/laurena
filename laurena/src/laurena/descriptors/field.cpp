///
/// \file     field.cpp
/// \brief    Describe a serializable field member in a class 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable field member in a class 
///

#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>

#include <laurena/descriptors/field.hpp>
#include <laurena/types/any.hpp>

#include <laurena/constants/const_charsets.hpp>
#include <laurena/constants/const_strings.hpp>
#include <laurena/toolboxes/bitset.hpp>

using namespace laurena;


field::field() : descriptable(""), _flags(field::FLAGS_MAX,0), _setter(nullptr), _getter(nullptr), _descriptor(nullptr), _values(nullptr)
{ }

field::field (const char* name, const descriptor* cd, word32 offset) : 
	descriptable(name) , _offset(offset), _descriptor(cd), _flags (field::FLAGS_MAX,0),  _setter(nullptr), _getter(nullptr), _values(nullptr)
{
}

field::~field()
{
}

field& field::init (const char* name, const descriptor* cd, word32 offset)
{
    if ( cd == nullptr ) 
    {
        std::string message ("you can't pass a nullptr descriptor for class ") ;
        message.append(name);
        throw new LAURENA_NULL_POINTER_EXCEPTION (message.c_str());
    }

    this->_name = name ;
    this->_offset = offset ;
    this->_descriptor = cd ;

    return *this;
}

field& field::init (field& source)
{
    if (source._descriptor == nullptr )
    {
        std::string message ("you can't pass a nullptr descriptor for class ") ;
        message.append(source._name);
        throw new LAURENA_NULL_POINTER_EXCEPTION (message.c_str());
    }

    this->_name = source._name ;
    this->_offset = source._offset ;
    this->_descriptor = source._descriptor ;
    this->_values = source._values;
    

    return *this;
}
    
field& field::init (const char* name, const descriptor* cd, setter setfunction, getter getfunction)
{
    if ( cd == nullptr ) 
    {
        std::string message ("you can't pass a nullptr descriptor for class ") ;
        message.append(name);
        throw new LAURENA_NULL_POINTER_EXCEPTION (message.c_str());
    }

    this->_name = name ;
    this->_descriptor = cd ;
	this->_setter = setfunction;
	this->_getter = getfunction;

    return *this;
}

void field::set(any& o, const any& value) const
{
	if (this->_setter != nullptr)
	{
		any v = this->desc().cast(value);		
		this->_setter (o,v);
		return;
	}

    void* optr = o.ptr();
    word8** ptr = memory::ptr(optr,this->_offset);
    if (this->_descriptor->has(descriptor::Flags::FIELDS))
    {
        if (this->_flags.test(field::FLAGS_IS_POINTER))
        {
            word8** destination = (word8**) ptr;
			word8* source = (word8*) value.ptr();
			*destination = source;
        }
    }
    else 
    {
        if (value.type() == typeid(std::string))
        {
            std::string svalue = anycast<std::string>(value);
            this->fromString(o,svalue);
        }
        else   
            this->_descriptor->set(ptr,value);       
    }
}

any& field::get(const any& object, any& value) const
{
	if (this->_getter != nullptr)
	{
		this->_getter ((any&) object,value);
		return value;
	}

    word8** ptr = memory::ptr(object.ptr(),this->_offset);
    if (this->isPointer())
        this->_descriptor->get(*ptr,value);
    else
        this->_descriptor->get(ptr,value);
    return value;
}

std::string& field::toString(const any& object, std::string& destination) const
{
    any value;

    if ( this->_getter )
    {
        any anydest;
        this->_getter((any&)object,anydest);
        return destination = std::move (anydest.desc()->atos(anydest));
    }


    this->get(object,value);


    destination = std::move(this->_descriptor->atos(value));
    if (this->_flags.test(field::FLAGS_IS_ENUM))
    {
        word32 index = boost::lexical_cast<word32,std::string>(destination);
        destination = this->_values->operator[](index);
    }
    else if (this->_flags.test(field::FLAGS_IS_BITSET))
    {
        if (this->_descriptor->has(descriptor::Flags::NUMERIC_VALUE))
        {
            word64 wbits = boost::lexical_cast<word64,std::string>(destination);
            bitset::serialize(wbits,*this->_values,destination,CONST_SPACE);            
        } 
        else
        if (const_charsets<>::BINARY.validate(destination))            
        {
            std::string bits = destination;
            bitset::serialize(bits,*this->_values,destination,CONST_SPACE);
        }
        else
            assert(false);
    }
    return destination;
}

void field::fromString(any& object, const std::string& svalue) const
{
any value;
void* ptrObject = object.ptr();
void* ptrAttribute = this->ptr(ptrObject);

    if (this->_flags.test(field::FLAGS_IS_ENUM))
    {
        int32 index = this->_values->find(svalue);
        if (index == -1)
        {
            std::string message (this->_name);
            message.append(",isEnum=true,value='").append(svalue).append("'), value not found in enum values.");
            throw LAURENA_FAILED_PARSING_EXCEPTION(message.c_str(),svalue.c_str());
        }

        value = index;
        this->_descriptor->set(ptrAttribute,value);
    }
    else if (this->_flags.test(field::FLAGS_IS_BITSET))
    {
        if (this->_descriptor->has(descriptor::Flags::NUMERIC_VALUE))
        {
            word64 b = bitset::parse(*this->_values,const_charsets<>::VARNAME,svalue);
            value = b;
            this->_descriptor->set(ptrAttribute,value);
        } 
        else if (this->_descriptor->type() == typeid(boost::dynamic_bitset<>))
        {
            boost::dynamic_bitset<>* p = (boost::dynamic_bitset<>*) ptrAttribute;
			if (p->size() != this->_values->size())
				p->resize(this->_values->size());
            bitset::parse(*p,*this->_values,const_charsets<>::VARNAME,svalue);
        }
        else
            assert(false);
    }
    else 
    {
        value = svalue;
        this->_descriptor->set(ptrAttribute,value);
    }
}

field& field::isEnum(const string_array& values)
{
    this->_flags.set(field::FLAGS_IS_ENUM);
    _values = &values;
    return *this;
}

bool field::isEnum() const
{
    return this->_flags.test(field::FLAGS_IS_ENUM);
}    

field& field::isBitSet(const string_array& values)
{
    this->_flags.set(field::FLAGS_IS_BITSET);
    _values = &values;
    return *this;
}

bool field::isBitSet() const
{
   return this->_flags.test(field::FLAGS_IS_BITSET);
}

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class fields                                               */ 
/*                                                                              */ 
/********************************************************************************/
fields::fields() : std::vector<std::unique_ptr<field>>() , _used(0)
{
}

field& fields::get(const std::string& name)
{
    for(std::unique_ptr<field>& f : *this)
        if (f->name() == name)
            return *f;

    std::string message (name);
	message.append (" is an unknow object field name.");
    throw new LAURENA_NULL_POINTER_EXCEPTION (message);
}

field* fields::find(const std::string& name)
{
    for(std::unique_ptr<field>& f : *this)
        if (f->name() == name)
            return f.get();

    return nullptr;
}

const field& fields::get(const std::string& name) const
{
    for(const std::unique_ptr<field>& f : *this)
        if (f->name() == name)
            return *f;

    std::string message (name);
	message.append (" is an unknow object field name.");
    throw new LAURENA_NULL_POINTER_EXCEPTION (message);
}

const field* fields::find(const std::string& name) const
{
    for(const std::unique_ptr<field>& f : *this)
        if (f->name() == name)
            return f.get();

    return nullptr;
}

field& fields::unused()
{
	std::unique_ptr<field> p (new field());
	this->push_back(std::move(p));

	return *(this->operator[](this->size()-1));
}
//end of file
