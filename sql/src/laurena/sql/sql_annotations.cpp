///
/// \file     sql_annotations.cpp
/// \brief    Annotations for sql persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// Annotations for sql persistance
///
#include <laurena/sql/sql_annotations.hpp>
#include <laurena/sql/sql_error.hpp>

using namespace laurena;
using namespace sql;

const char* sql_tablename::ANNOTATION_NAME = "sql_tablename";
const char* sql_column::ANNOTATION_NAME = "sql_column";

/********************************************************************************/ 
/*																				*/ 
/*		code for class sql_tablename											*/ 
/*																				*/
/********************************************************************************/ 

sql_tablename::sql_tablename (const char* tablename) : annotation (sql_tablename::ANNOTATION_NAME), _tablename(tablename), _primary_key(nullptr)
{ }


bool sql_tablename::acceptDescriptable()
{
	return nullptr != dynamic_cast<descriptor*>(this->_descriptable);
}
/********************************************************************************/ 
/*																				*/ 
/*		code for class sql_column   											*/ 
/*																				*/
/********************************************************************************/ 

sql_column::sql_column (const char* column, word32 mask) : annotation(sql_column::ANNOTATION_NAME), _column(column), 
	_primary_key( (mask & PRIMARY_KEY) != 0),
	_auto_increment( (mask & AUTO_INCREMENT) != 0), 
	_unique ( (mask & UNIQUE) != 0), 
	_not_null ( (mask & NOT_NULL) != 0)
{

}

bool sql_column::acceptDescriptable()
{
	return nullptr != dynamic_cast<field*>(this->_descriptable);
}

void sql_column::annotated()
{
	/* 
	const field*f = dynamic_cast<field*>(this->_descriptable);
	const sql_tablename* t = dynamic_cast<const sql_tablename*>(f->desc().annotations().get(sql_tablename::ANNOTATION_NAME));

	if (!t)
		sql_error::columnButNoTablename(*f);

	if (t->_primary_key)
		sql_error::twoPrimaryKeys(f->desc());

	((sql_tablename*)t)->_primary_key = f;
	*/ 
}
//End of fil
