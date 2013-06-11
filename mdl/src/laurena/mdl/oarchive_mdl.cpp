///
/// \file     oarchive_mdl.cpp
/// \brief    Base class for an output archive i.e a class to serialize a class into a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an output archive i.e a class to serialize a class into a file format.
///
#include <laurena/mdl/oarchive_mdl.hpp>
#include <laurena/mdl/language_mdl.hpp>

using namespace laurena;
using namespace mdl;

oarchive_mdl::oarchive_mdl() : oarchive ()
{
    this->_injection = false;
    this->_format = formats.get("mdl");
}


oarchive_mdl::~oarchive_mdl()
{
}


void oarchive_mdl::serializeFields(const descriptor& cd, const any& value)
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
        const field& att = myFields[i];        
        if (att.isPrimaryKey())
            continue;

        att.get(value,fieldValue);

        if (this->_format)
        {
            const format* fieldFormat = this->_format->find_field(att);
            if ( fieldFormat )
            {
                this->_data << this->_tab << att.name() << " = " ;
                fieldFormat->write(this->_data , fieldValue);
                continue;
            }

            const format* typeFormat = this->_format->find_type(att.desc());
            if (typeFormat)
            {
                this->_data << this->_tab << att.name() << " = " ;
                typeFormat->write(this->_data,fieldValue);
                this->_data << ";" << std::endl;
                continue;
            }
        }

        const descriptor& acd = att.desc();
        acf = dynamic_cast<const any_feature*>(acd.feature(Feature::ANY));
               
        void* vptr = att.ptr(ptrObject);

        if (acf)
        {
            if (acf->isEmpty(vptr))
                continue;

            const descriptor& ccd = acf->desc(vptr);
            if (ccd.has(descriptor::Flags::FIELDS))
            {
                //vptr = (void*) * boost::unsafe_any_cast<void**>((boost::any*)vptr);
                this->serialize(att.name(),fieldValue,true);
                return ;
            }
        }

        if (acd.has(descriptor::Flags::FIELDS))
        {
            this->serialize(att.name(),fieldValue,false);

        }
        else                
        {
            if ( att.ignoreIfDefaultValue())
            {
                if (acd.equals(att.defaultValue(),fieldValue))
                    continue;
            }

            bool isString = false;
            

            att.toString(value,s);
            if (acd.type() == typeid(std::string))
                isString = true;
            else
            {
                if ( !att.isEnum() && !att.isBitSet())
                   if (acd.has(descriptor::Flags::NUMERIC_VALUE) == false)
                        isString |= !stdstring::isInteger(s);
            }

            this->_data << this->_tab << att.name() << " = " ;

            if (acf)
            {
                
                this->_data << "(" << acf->desc(vptr).name() << ") ";  
            }

            if (isString)
                this->_data << "\"";

            this->_data << s;

            if (isString)
                this->_data << "\"";

            this->_data << ";" << std::endl;           
        }
    }
}

void oarchive_mdl::serializeElements(const descriptor& cd, const any& value)
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

				this->serialize(keystr,element,true);
			}
			else
			{
	
				this->serialize(keystr,element,false);
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


oarchive& oarchive_mdl::serialize(const std::string& name, const any& value,bool injection)
{
const descriptor* cd = value.desc();

    if ( !cd)
    {
        throw new LAURENA_NULL_POINTER_EXCEPTION("In oarchive::serialize, any& value do have NULL descriptor.");
    }

    // opening
    this->_data << this->_tab << name ;

    if (injection)
    {
        this->_data << " <- new " << value.desc()->name() << " " ;
    }


    this->_data << ":" ;        
    if (cd->has(descriptor::Flags::PRIMARY_KEY))
    {
        std::string s;
        cd->primaryKey().toString(value,s);
        if (s.length())
            this->_data << s;
        else
            this->_data << "_";
    }
    else
        this->_data << "_";

    this->_data << std::endl << this->_tab << "{" << std::endl;
    this->_tab += "  ";


    if (cd->has(descriptor::Flags::FIELDS))
        this->serializeFields(*cd,value);   

    if (cd->hasFeature(Feature::CONTAINER))
        this->serializeElements(*cd,value);


    this->_tab.erase(this->_tab.length()-2);

    this->_data << this->_tab << "}" << std::endl;
    
    if (this->_tab.length() == 0)
        this->_data.flush();

    return *this;
}

void oarchive_mdl::save(const std::string& filename, const std::string& name, const any& value)
{
    oarchive_mdl amdl;
    amdl.serialize(name,value,false);
   
    std::ofstream output (filename.c_str(),std::ios_base::in);
    std::string s = amdl.str();
    output.write(s.c_str(),s.length());
    output.close();    

}

std::string& oarchive_mdl::tostring(std::string& destination, const std::string& name, const any& value, word32 flags)
{
    oarchive_mdl omdl;
    //if ( flags & MDL::COMPACT )

    omdl.serialize(name,value,false);

    return destination = omdl.str();
}
//end of file
