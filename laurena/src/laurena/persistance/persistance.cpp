///
/// \file     persistance.cpp
/// \brief    Generic persistance engine
/// \author   Frederic Manisse
/// \version  1.0
///
/// Generic persistance engine
///
#include <laurena/persistance/persistance.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/descriptors/field.hpp>

using namespace laurena;

void persistance::add(const std::string& pipeline, dao::sptr pdao)
{
   this->_daos [pipeline] = pdao;
}

void persistance::add (const std::string& pipeline, serial_manager::sptr pserial)
{
    this->_serial_managers[pipeline] = pserial;
}

void persistance::insert(const std::string& pipeline, any object)
{
const descriptor* desc = object.desc();

    auto it = this->_daos.find(pipeline);
    if (it == this->_daos.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }    

    dao::sptr& d = it->second;

    if (!d->serial_manager().empty())
    {
        auto it2 = this->_serial_managers.find(d->serial_manager());
        if (it2 != this->_serial_managers.end())
        {
            serial_manager::sptr ser = it2->second;
            any serialKey, primaryKey;

            if (!desc->has(descriptor::Flags::SERIAL))
            {
                std::ostringstream ss;
                ss << "An instance of class '" << desc->name() << "' has been asked to persistance with pipeline serial '" 
                   << d->serial_manager () << "' but the class doesn't have any serial key."
                   ;
                throw LAURENA_EXCEPTION(ss.str());

            }

            desc->serial().get(object, serialKey);
            desc->primaryKey().get(object, primaryKey);

            serial_entry entry;
            entry._serial = serialKey.tos();
            if (!ser->is_valid_serial(entry._serial))
            {
                entry._serial = boost::lexical_cast<std::string>(ser->new_serial());
                any a (entry._serial);
                object.desc()->serial().set(object, a);
            }
            entry._pipeline = pipeline;
            entry._primary_key = primaryKey.tos();
            const descriptor *desc = object.desc();
            if (!desc)
            {
                throw LAURENA_NULL_POINTER_EXCEPTION("Class descriptor not found");
            }
            entry._descriptor_name = desc->name();
            ser->write(entry);
        }
    }

    d->create(object);
}

void persistance::select(const std::string& pipeline, const any& key, any destination, persistance::SELECTOR selector)
{
    switch(selector)
    {
        case persistance::PRIMARY_KEY:
            this->select_by_primary_key(pipeline, key, destination);
            break;

        case persistance::SERIAL_KEY:
            this->select_by_serial_key(pipeline, key, destination);
            break;
        default:
            assert(false);
    }
}

any persistance::serial_to_object (const std::string& pipeline, const std::string& key)
{
    auto it = this->_serial_managers.find(pipeline);
    if (it == this->_serial_managers.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }
    serial_entry entry;
    it->second->read(entry, key);

    const descriptor* desc = classes::by_name(entry._descriptor_name);
    if (!desc)
    {
        std::string s = "Class " ;
        s.append(entry._descriptor_name).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }

    any res (desc->create());
    this->select_by_primary_key(entry._pipeline, entry._primary_key, res);

    return res;
}

void persistance::select_by_serial_key(const std::string& pipeline, const any& serialKey, any& destination)
{
    auto it = this->_serial_managers.find(pipeline);
    if (it == this->_serial_managers.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }
    serial_entry entry;
    it->second->read(entry, serialKey.tos());

    this->select_by_primary_key(entry._pipeline, entry._primary_key, destination);

}


void persistance::select_by_primary_key(const std::string& pipeline, const any& primaryKey, any& destination)
{
    auto it = this->_daos.find(pipeline);
    if (it == this->_daos.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }
    it->second->read(primaryKey, destination);
}

bool persistance::exist(const std::string& pipeline, const any& primaryKey)
{
    auto it = this->_daos.find(pipeline);
    if (it == this->_daos.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }
    return it->second->exist(primaryKey);
}
//End of file
