///
/// \file     sql.hpp
/// \brief    Main file to include to use the SQL persistance library
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Main file to include to use the SQL persistance library
///
#ifndef LAURENA_SQL_H
#define LAURENA_SQL_H

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

#include <laurena/sql/sql_annotations.hpp>
#include <laurena/sql/sql_dao.hpp>
#include <laurena/sql/sql_database.hpp>
#include <laurena/sql/sql_statement.hpp>

#endif
//End of file
