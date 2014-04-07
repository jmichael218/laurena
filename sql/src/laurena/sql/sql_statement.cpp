///
/// \file     sql_statement.cpp
/// \brief    interface to a statement
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to a statement
///
#include <laurena/sql/sql_statement.hpp>

using namespace laurena;
using namespace sql;

sql_statement::sql_statement(sql_database& db, const std::string& query) : _db(db), _query(query)
{ }

sql_statement::~sql_statement()
{ }

bool sql_statement::has_data()
{
    return false;
}

int8 sql_statement::i8    (word16 column_index)
{
    return 0;
}

int16 sql_statement::i16   (word16 column_index)
{
    return 0;
}

int32 sql_statement::i32   (word16 column_index)
{
    return 0;
}

int64 sql_statement::i64   (word16 column_index)
{
    return 0;
}

const char* sql_statement::cstr  (word16 column_index)
{
    return nullptr;
}

std::string sql_statement::str   (word16 column_index)
{
    return std::string("");
}
//End of file
