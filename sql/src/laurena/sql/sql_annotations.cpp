///
/// \file     sql_annotations.cpp
/// \brief    Annotations for sql persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// Annotations for sql persistance
///
#include <laurena/sql/sql_annotations.hpp>

using namespace laurena;
using namespace sql;

sql_tablename::sql_tablename (const char* tablename) : annotation ("sql_tablename"), _tablename(tablename)
{ }

sql_column::sql_column (const char* column, word32 mask) : annotation("sql_column"), _column(column), 
	_primary_key( (mask & PRIMARY_KEY) != 0),
	_auto_increment( (mask & AUTO_INCREMENT) != 0), 
	_unique ( (mask & UNIQUE) != 0), 
	_not_null ( (mask & NOT_NULL) != 0)
{
}

//End of fil
