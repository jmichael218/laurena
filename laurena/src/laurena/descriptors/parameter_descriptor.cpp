///
/// \file     parameter_descriptor.cpp
/// \brief    descriptors for class parameter
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for class parameter
///
#include <laurena/descriptors/parameter_descriptor.hpp>
#include <laurena/descriptors/const_ptr_descriptor_descriptor.hpp>
#include <laurena/descriptors/bitset_descriptor.hpp>
#include <laurena/descriptors/vector_descriptor.hpp>
#include <laurena/formatting/format_bitset.hpp>
#include <laurena/constants/const_strings.hpp>

using namespace laurena;

const descriptor* td<parameter>::desc()
{
    static standard_class_descriptor<parameter>* res = nullptr;
    if (res == nullptr)
    {
        res = standard_class_descriptor<parameter>::build("parameter");       

		res->add_field(&parameter::_name, "name");

		const descriptor * cdesc = td<const descriptor *>::desc();
		res->editFields().unused().init("type", cdesc, offsetof(parameter, _descriptor)).is_pointer(true).no_quote(true);
	
		res->add_field(&parameter::_flags, "flags").annotate(new format_bitset(ANNOTATION_FORMAT_ALL, parameter::FlagsKeywords));
    }

    return res;
}

const descriptor* td<parameters>::desc()
{
    static vector_descriptor<parameters, parameter>* res = nullptr;
    if (res == nullptr)
    {
		res = vector_descriptor<parameters, parameter>::build("parameters");
	}
	return res;
}
//End of file