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

using namespace laurena;

void persistance::add(const std::string& pipeline, dao::sptr pdao)
{
   this->_daos [pipeline] = pdao;
}

void persistance::create(const std::string& pipeline, any object)
{
    auto it = this->_daos.find(pipeline);
    if (it == this->_daos.end())
    {
        std::string s = "Pipeline " ;
        s.append(pipeline).append(" not found.");
        throw LAURENA_NULL_POINTER_EXCEPTION(s);
    }

    it->second->create(object);
}