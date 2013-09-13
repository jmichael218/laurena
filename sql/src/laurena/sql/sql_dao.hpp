///
/// \file     sql_dao.hpp
/// \brief    DAO base class and templated class
/// \author   Frederic Manisse
/// \version  1.0
///
/// Annotations for sql persistance
///
#ifndef LAURENA_SQL_DAO_H
#define LAURENA_SQL_DAO_H

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
/* sql dao                                                                      */ 
/********************************************************************************/ 

class dao
{
public:

	std::string generateInsertStatement(const descriptor& desc, const any& object);
	std::string generateSelectByPrimaryKey(const descriptor& desc, any& primary_key);

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file