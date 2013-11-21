///
/// \file     mdl_interface.hpp
/// \brief    interface to mask internal calls to serialize from/to mdl
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to mdl
///
#include <laurena/mdl/iarchive_mdl.hpp>
#include <laurena/mdl/oarchive_mdl.hpp>
#include <laurena/mdl/mdl_interface.hpp>

using namespace laurena;
using namespace mdl;

std::string& laurena::mdl::mdl::serialize(std::string& destination, const std::string& name, const any& value)
{
    oarchive_mdl a;

    a.serialize(name,value,false);

    return destination = a.str();
}
//End of file
