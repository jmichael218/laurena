///
/// \file     laurena.hpp
/// \brief    Include standard header files 
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This file include all the headers needed to use the Core library
//
#ifndef LAURENA_H
#define LAURENA_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// base files
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

// memory related
#include <laurena/memory/memory_functions.hpp>

// debug
#include <laurena/debug/debug.hpp>
#include <laurena/debug/testunit.hpp>
#include <laurena/debug/debug_stream.hpp>

// exceptions
#include <laurena/exceptions/exception.hpp>
#include <laurena/exceptions/bad_cast_exception.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>
#include <laurena/exceptions/file_not_found_exception.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/exceptions/unimplemented_exception.hpp>

// traits
#include <laurena/traits/basetype.hpp>
#include <laurena/traits/voidptr.hpp>

// templates

// generic descriptors
#include <laurena/descriptors/descriptor.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/descriptors/classes.hpp>
#include <laurena/descriptors/method_descriptor.hpp>
#include <laurena/descriptors/polymorphic_class_descriptor.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/descriptors/string_descriptor.hpp>
#include <laurena/descriptors/simple_type_descriptor.hpp>
#include <laurena/descriptors/numeric_type_descriptors.hpp>
#include <laurena/descriptors/list_descriptor.hpp>
#include <laurena/descriptors/vector_descriptor.hpp>

// class features
#include <laurena/descriptors/features/class_feature.hpp>
#include <laurena/descriptors/features/class_features.hpp>
#include <laurena/descriptors/features/polymorphic_feature.hpp>
#include <laurena/descriptors/features/any_feature.hpp>
#include <laurena/descriptors/features/keymapper_feature.hpp>
#include <laurena/descriptors/features/container_feature.hpp>

// types
#include <laurena/types/any.hpp>
#include <laurena/types/charset.hpp>
#include <laurena/types/string_array.hpp>
#include <laurena/types/variable.hpp>
#include <laurena/types/literator.hpp>
#include <laurena/types/context.hpp>

// toolboxes
#include <laurena/toolboxes/bitset.hpp>
#include <laurena/toolboxes/stdstring.hpp>
#include <laurena/toolboxes/cstring.hpp>
#include <laurena/toolboxes/loader.hpp>
#include <laurena/toolboxes/filename.hpp>
#include <laurena/toolboxes/stdstream.hpp>

// laurena traits
#include <laurena/traits/laurena_traits.hpp>

// specific descriptors
#include <laurena/descriptors/any_descriptor.hpp>
#include <laurena/descriptors/variable_descriptor.hpp>
#include <laurena/descriptors/string_array_descriptor.hpp>
#include <laurena/descriptors/bitset_descriptor.hpp>

//parsing
#include <laurena/parsing/token.hpp>
#include <laurena/parsing/file_location.hpp>
#include <laurena/parsing/parser.hpp>
#include <laurena/parsing/tokenizer.hpp>
#include <laurena/parsing/basic_parsers.hpp>

//archives
#include <laurena/archives/oarchive.hpp>
#include <laurena/archives/iarchive.hpp>

// constants
#include <laurena/constants/const_strings.hpp>
#include <laurena/constants/const_charsets.hpp>

// functions
#include <laurena/functions/parameter.hpp>

//formatters
#include <laurena/formatting/writer.hpp>
#include <laurena/formatting/format.hpp>
#include <laurena/formatting/tab.hpp>


#endif
//end of file
