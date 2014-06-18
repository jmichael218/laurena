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


field::field() : descriptable(""), _flags(), _setter(nullptr), _getter(nullptr), _descriptor(nullptr), _values(nullptr)
{ }

field::field (const char* name, const descriptor* cd, word32 offset) : 
	descriptable(name) , _offset(offset), _descriptor(cd), _flags (),  _setter(nullptr), _getter(nullptr), _values(nullptr)
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
            this->froms(o,svalue);
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
    if (this->is_pointer())
        this->_descriptor->get(*ptr,value);
    else
        this->_descriptor->get(ptr,value);
    return value;
}

std::string& field::tos(const any& object, std::string& destination) const
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

    return destination;
}

void field::froms(any& object, const std::string& svalue) const
{
any value;
void* ptrObject = object.ptr();
void* ptrAttribute = this->ptr(ptrObject);

	value = svalue;
    this->_descriptor->set(ptrAttribute,value);
    
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

int fields::index(const std::string& name) const
{
    for(size_t i = 0; i < this->size(); ++i)
        if (this->at(i)->name() == name)
            return i;

    return 0xFFFF;
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
