///
/// \file     oarchive_mdl.cpp
/// \brief    Base class for an output archive i.e a class to serialize a class into a file format.
/// \author   Frederic Manisse
/// \version  1.0
///
/// Base class for an output archive i.e a class to serialize a class into a file format.
///
#include <laurena/json/oarchive_json.hpp>
#include <laurena/json/language_json.hpp>

using namespace laurena;
using namespace json;

oarchive_json::oarchive_json() : oarchive () , _compact (false) , _tab ("\t"), _nb_fields(0), _depth(0)
{
    this->_format = formats.get("json");
}


oarchive_json::~oarchive_json()
{
}

void oarchive_json::completeLastLine()
{
    ++ this->_nb_fields ;
    if ( this->_nb_fields != 1)
		this->_data << ",";

	if (!this->_compact)
		this->_data << std::endl;
 
       
}

void oarchive_json::printFieldName(const field& att)
{
	if ( !this->_compact)
		this->_data << this->_tab << "\"" << att.name() << "\": ";
    else
        this->_data << "\"" << att.name() << "\":";
}

void oarchive_json::serializeFields(const descriptor& cd, const any& value)
{
std::string s;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(cd.feature(Feature::POLYMORPHIC));
const any_feature* acf = NULL;

    if (pcf && pcf->hasParent())
        this->serializeFields(pcf->parent(),value);

    if (cd.has(descriptor::Flags::FIELDS) == false) 
        return;

    const fields& myFields = cd.getFields();
    word32 nbAttributes = myFields.size();

    void* ptrObject = value.ptr();
    any fieldValue;

    for (word32 i = 0; i < nbAttributes; ++i)
    {                

        this->completeLastLine();

        const field& att = myFields[i];        
        att.get(value,fieldValue);       



        if (this->_format)
        {
            const format* fieldFormat = this->_format->find_field(att);
            if ( fieldFormat )
            {                
                fieldFormat->write(this->_data , fieldValue);               
                continue;
            }

            const format* typeFormat = this->_format->find_type(att.desc());
            if (typeFormat)
            {               
                typeFormat->write(this->_data,fieldValue);                
                continue;
            }
        }

        const descriptor& acd = att.desc();
     
        void* vptr = att.ptr(ptrObject);

        if (acd.has(descriptor::Flags::FIELDS))
        {            
			this->printFieldName(att);
			if (!this->_compact)
				this->_data << std::endl;
            this->serializeObject(fieldValue);
        }
		else if (acd.hasFeature(Feature::CONTAINER)) 
		{
			this->printFieldName(att);
			if (!this->_compact)
				this->_data << std::endl;
			this->serializeObject(fieldValue);
		}
        else                
        {
            if ( att.ignoreIfDefaultValue())
            {
                if (acd.equals(att.defaultValue(),fieldValue))
                    continue;
            }

			this->printFieldName(att);
            bool isString = false;
            

            att.toString(value,s);
            if (acd.type() == typeid(std::string))
                isString = true;
            else
            {
                if ( !att.isEnum() && !att.isBitField())
                   if (acd.has(descriptor::Flags::NUMERIC_VALUE) == false)
                        isString |= !stdstring::isInteger(s);
            }


            if (isString)
                this->_data << "\"";

            this->_data << s;

            if (isString)
                this->_data << "\"";
      
        }
    }
    
}

void oarchive_json::serializeElements(const descriptor& cd, const any& value)
{

const container_feature* ccf = dynamic_cast<const container_feature*>(cd.feature(Feature::CONTAINER));

    if (!ccf)
        return;

    bool hasKey = ccf->hasKey();

    const descriptor* ecd = ccf->elementDescriptor();
    const descriptor* kcd = hasKey ? ccf->keyDescriptor() : NULL;

    any element, key, mapped;
    std::string keystr, elementstr;

    ccf->begin(value);
    

    for (literator it = ccf->begin(value); it != ccf->end(value); ++it)
    {

		this->completeLastLine();

        // get key 
        if ( hasKey )
        {

            key = it.key();        
            kcd->toString(key,keystr);            
        }
        else
        {
            keystr = ecd->name();
        }

        element = *it;
       
        const format* typeFormat = this->_format ? this->_format->find_type(*ecd) : nullptr;
        if (typeFormat)
        {
            this->_data << this->_tab << keystr << " = " ;
            typeFormat->write(this->_data,element);
            continue;
        }

        if (ecd->has(descriptor::Flags::FIELDS))
        {
			if (ccf->areElementsPointers())
			{
                if (element.isEmpty())
                    continue;

				this->serializeObject(element);
			}
			else
			{
	
				this->serializeObject(element);
			}
        }
        else
        {            

            this->_data << this->_tab << keystr << " = " ;
                    
            ecd->toString(element,elementstr);
            bool isString = false;
            if (ecd->type() == typeid(std::string))
                isString = true;
            else
                isString |= !stdstring::isInteger(elementstr);
            

            if (isString)
                this->_data << "\"";

            this->_data << elementstr;

            if (isString)
                this->_data << "\"";

            this->_data << ";" << std::endl;  
        }   
         
    }

}

void oarchive_json::serializeObject(const any& value)
{
const descriptor* cd = value.desc();

    if ( !cd)
    {
        throw new LAURENA_NULL_POINTER_EXCEPTION("In oarchive::serialize, any& value do have nullptr descriptor.");
    }

    word32 backup = this->_nb_fields;
    this->_nb_fields = 0;

	std::string opening = "{";
	std::string ending = "}" ;

	if (cd->hasFeature(Feature::CONTAINER))
	{
		opening = "[" ;
		ending = "]" ;
	}

    // opening
	if (this->_compact) 
		this->_data << opening ;
	else
	{
		this->_data << this->_tab << opening << std::endl;
		this->_tab.increase();
	}


    if (cd->has(descriptor::Flags::FIELDS))
        this->serializeFields(*cd,value);   

    if (cd->hasFeature(Feature::CONTAINER))
        this->serializeElements(*cd,value);

	if (this->_compact)
		this->_data << ending ;
	else 
	{
		this->_data << std::endl << this->_tab.decrease() << ending ;
	}

    this->_nb_fields = backup;
}

oarchive& oarchive_json::serialize(const std::string& name, const any& value,bool injection)
{

   if (this->_compact) 
		this->_data << "{" << "\"" << name << "\":";
	else
	{
			this->_data << this->_tab << "{" << std::endl;
			this->_data << this->_tab.increase() <<  "\"" << name << "\":" << std::endl;

	}
	
   this->serializeObject(value);


	if (this->_compact)
		this->_data << "}" ;
	else 
	{

		this->_data << std::endl << this->_tab.decrease() << "}" ;
	}
    return *this;
}


//end of file
