///
/// \file     xml_oarchive.cpp
/// \brief    Class for a XML output archive i.e a class to serialize a class instance from a XML file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a XML output archive i.e a class to serialize a class instance from a XML file format.
///
#include <laurena/validations/is_integer.hpp>

#include <laurena/xml/xml_oarchive.hpp>
#include <laurena/xml/xml_language.hpp>

using namespace laurena;
using namespace xml;

oarchive_xml::oarchive_xml() : oarchive ()
{ }


oarchive_xml::~oarchive_xml()
{ }


void oarchive_xml::serializeFields(const descriptor& cd, const any& value)
{
std::string s;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(cd.feature(Feature::POLYMORPHIC));
const any_feature* acf = NULL;

    if (pcf && pcf->has_parent())
        this->serializeFields(pcf->parent(),value);

    if (cd.has(descriptor::Flags::FIELDS) == false) 
        return;

    void* ptrObject = value.ptr();
    any fieldValue;

    for (const std::unique_ptr<field>& patt : cd.get_fields())
    {             
		field& att = *patt;
        if (att.is_primary_key())
            continue;

        att.get(value,fieldValue);

        const format* fieldFormat = dynamic_cast<const format*>(att.annotations().get(XML::ANNOTATION_NAME, ANNOTATION_FORMAT_ALL));
        if ( fieldFormat )
        {
            this->_data << this->_tab << "<" << att.name() << ">" ;
            fieldFormat->write(this->_data , fieldValue);
            this->_data << "</" << att.name() << ">" << std::endl;
            continue;
        }

        const format* typeFormat = dynamic_cast<const format*>(att.desc().annotations().get(XML::ANNOTATION_NAME, ANNOTATION_FORMAT_ALL));
        if (typeFormat)
        {
            this->_data << this->_tab << "<" << att.name() << ">" ;
            typeFormat->write(this->_data,fieldValue);
            this->_data << "</" << att.name() << ">" << std::endl;
            continue;            
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
            if ( att.ignore_if_default_value())
            {
                if (acd.equals(att.default_value(),fieldValue))
                    continue;
            }

            att.tos(value,s);

            this->_data << this->_tab << "<" << att.name() << ">"
                        << s
                        << "</" << att.name() << ">" << std::endl
                        ;          
        }
    }
}

void oarchive_xml::serializeElements(const descriptor& cd, const any& value)
{

const container_feature* ccf = dynamic_cast<const container_feature*>(cd.feature(Feature::CONTAINER));
const keymapper_feature* mapper = dynamic_cast<const keymapper_feature*>(cd.feature(Feature::KEY_MAPPER));

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
			if (mapper)
			{
				mapper->map(value, key, mapped);
				keystr = std::move(mapped.tos());
			}
			else
				keystr = std::move( kcd->atos(key));            
        }
        else
        {
            keystr = ecd->name();
        }

        element = *it;
       
        const format* typeFormat = dynamic_cast<const format*>(ecd->annotations().get(XML::ANNOTATION_NAME));
        if (typeFormat)
        {
            this->_data << this->_tab << "<" << cd.name() << ">";
            typeFormat->write(this->_data,element);
            this->_data << "</" << cd.name() << ">" << std::endl;
            continue;
        }

        if (ecd->has(descriptor::Flags::FIELDS))
        {
			if (ccf->areElementsPointers())
			{
                if (element.empty())
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
            elementstr = std::move (ecd->atos(element));
            this->_data << this->_tab << "<" << cd.name() << ">"
                        << elementstr
                        << "</" << cd.name() << ">" << std::endl;

        }   
         
    }
}


oarchive& oarchive_xml::serialize(const std::string& name, const any& value,bool injection)
{
const descriptor* cd = value.desc();

    if ( !cd)
    {
        throw new LAURENA_NULL_POINTER_EXCEPTION("any& value do have NULL descriptor.");
    }

    // opening
    this->_data << this->_tab << "<" <<name << ">" << std::endl;

    this->_tab += "  ";


    if (cd->has(descriptor::Flags::FIELDS))
        this->serializeFields(*cd,value);   

    if (cd->hasFeature(Feature::CONTAINER))
        this->serializeElements(*cd,value);


    this->_tab.erase(this->_tab.length()-2);

    this->_data << this->_tab << "</" << name << ">" << std::endl;
    
    if (this->_tab.length() == 0)
        this->_data.flush();

    return *this;
}

void oarchive_xml::save(const std::string& filename, const std::string& name, const any& value)
{
    oarchive_xml oxml;
    oxml.serialize(name,value,false);
   
    std::ofstream output (filename.c_str(),std::ios_base::in);
    std::string s = oxml.str();
    output.write(s.c_str(),s.length());
    output.close();    

}

std::string& oarchive_xml::tostring(std::string& destination, const std::string& name, const any& value, word32 flags)
{
    oarchive_xml oxml;
    //if ( flags & MDL::COMPACT )

    oxml.serialize(name,value,false);

    return destination = oxml.str();
}
//end of file
