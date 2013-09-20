///
/// \file     sql_toolbox.hpp
/// \brief    Toolbox of functions for sql persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// Toolbox of functions for sql persistance
///
#ifndef LAURENA_SQL_TOOLBOX_H
#define LAURENA_SQL_TOOLBOX_H

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

class sql_toolbox
{
public:

	static const field* primaryKeyField(const descriptor& desc);
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file