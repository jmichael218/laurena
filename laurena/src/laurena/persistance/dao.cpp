///
/// \file     dao.cpp
/// \brief    DAO base class and templated class
/// \author   Frederic Manisse
/// \version  1.0
///
/// DAO base class and templated class
///
#include <laurena/persistance/dao.hpp>

using namespace laurena;

dao::dao (const descriptor& desc) : _descriptor(desc)
{ }

dao::~dao()
{ }

any dao::read    (const any& primaryKey)
{
    any a;
    this->read(primaryKey, a);
    return a;
}
//End of file