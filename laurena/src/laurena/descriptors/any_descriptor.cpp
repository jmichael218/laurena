/// \file     any_descriptor.cpp
/// \brief    A special class descriptor for laurena::any
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A special class descriptor for laurena::any
///


#include <laurena/descriptors/any_descriptor.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/descriptors/features/class_features.hpp>
#include <laurena//types/any.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*              code for class AnyClassFeatureImpl                              */ 
/*                                                                              */
/********************************************************************************/ 
any_feature_impl::any_feature_impl(const descriptor* desc) 
                    : any_feature(desc) 
{
}

bool any_feature_impl::isAny () const
{
    return true;
}

const descriptor& any_feature_impl::desc(void* ptrValue) const
{
    any* pany = (any*) ptrValue;
    const descriptor* res = pany->desc();
    if (!res)
        throw new LAURENA_NULL_POINTER_EXCEPTION("unkwow class descriptor");

    return *res;
}

bool any_feature_impl::isEmpty (void* ptrValue) const
{
any* pany = (any*) ptrValue;

    return pany->empty();
}

/********************************************************************************/ 
/*                                                                              */ 
/*              code for class AnyClassDescriptor                               */ 
/*                                                                              */ 
/********************************************************************************/ 
any_descriptor::any_descriptor()
	: descriptor("any",typeid(any)) , _any_class_feature(this)
{ }

const class_feature* any_descriptor::feature(Feature featureId) const
{
    if (featureId == Feature::ANY)
        return &this->_any_class_feature;

    return this->descriptor::feature(featureId);
}
// ACCESSORS
void any_descriptor::set(void* ptr, const any& value)  const
{
	any* p = (any*) ptr;   
	*p = value;
}

any& any_descriptor::get(void* ptr, any& value)  const
{
	any* p = (any*) ptr;
	value = *p;
	return value;
}

// TO/FROM STRING SERIALIZATION 
std::string any_descriptor::atos(const any& value) const
{
	const descriptor* cd = value.desc();
	if (!cd)
	{
		throw LAURENA_NULL_POINTER_EXCEPTION("unknow class descriptor");
	}
	return cd->atos(value);

}
//End of file
