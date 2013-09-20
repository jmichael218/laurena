///
/// \file     sql_error.hpp
/// \brief    Toolbox of functions to generate errors
/// \author   Frederic Manisse
/// \version  1.0
///
/// Toolbox of functions for sql persistance
///
#ifndef LAURENA_SQL_ERROR_H
#define LAURENA_SQL_ERROR_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace sql {

/********************************************************************************/ 
/* sql tool box                                                                 */ 
/********************************************************************************/ 

class sql_error
{
public:

	static void noPrimaryKey(const descriptor& desc);
	static void twoPrimaryKeys(const descriptor& desc);
	static void columnButNoTablename(const field& f);
	static void noTablename(const descriptor& desc);
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file