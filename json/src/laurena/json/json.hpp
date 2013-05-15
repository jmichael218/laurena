///
/// \file     json.hpp
/// \brief    Main file to include to use the JSON language as output/input for serializations.
/// \author   Frederic Manisse
/// \version  1.0
///
/// Main file to include to use the JSON language as output/input for serializations.
///
#ifndef LAURENA_JSON_H
#define LAURENA_JSON_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

#include <laurena/json/oarchive_json.hpp>
#include <laurena/json/iarchive_json.hpp>
#include <laurena/json/language_json.hpp>
#include <laurena/json/json_interface.hpp>

#endif
//End of file

