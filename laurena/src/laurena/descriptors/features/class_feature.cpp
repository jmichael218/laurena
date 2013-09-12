///
/// \file     class_feature.hpp
/// \brief    Implementation of a special feature for a class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Implementation of a special feature for a class
///
#include <laurena/descriptors/features/class_feature.hpp>
#include <laurena/exceptions/exception.hpp>

using namespace laurena;

class_feature::class_feature(const descriptor* desc) : _descriptor(desc)
{
    if(_descriptor == nullptr)
        throw new LAURENA_EXCEPTION("descriptor is nullptr.");

}

class_feature::~class_feature()
{
}

//End of file

