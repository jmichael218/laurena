///
/// \file     xml.hpp
/// \brief    Main file to include to use the XML language as output/input for serializations.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Main file to include to use the XML language as output/input for serializations.
///
#ifndef LAURENA_XML_H
#define LAURENA_XML_H

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

#include <laurena/xml/xml_oarchive.hpp>
#include <laurena/xml/xml_iarchive.hpp>
#include <laurena/xml/xml_language.hpp>
#include <laurena/xml/xml_interface.hpp>
#include <laurena/xml/xml_dao.hpp>

#endif
//End of file

