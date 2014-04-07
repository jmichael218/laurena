///
/// \file     sqlite_statement.cpp
/// \brief    SQLite implementation of class sql_statement
/// \author   Frederic Manisse
/// \version  1.0
///
/// SQLite implementation of class sql_statement
///
#include <laurena/sql/sqlite/sqlite_statement.hpp>

using namespace laurena;
using namespace sql;

sqlite_statement::sqlite_statement (sql_database& db, sqlite3_stmt* statement, const std::string& query) : sql_statement(db, query), _statement(statement)
{ 
    this->_last_step_result = sqlite3_step(this->_statement);
}

sqlite_statement::~sqlite_statement ()
{ 
    if (this->_statement != nullptr)
    {
        sqlite3_finalize(this->_statement);
        this->_statement = nullptr;
    }
}

bool sqlite_statement::has_data()
{
    return this->_last_step_result == SQLITE_ROW;
}

int8 sqlite_statement::i8    (word16 column_index)
{
    return (int8) sqlite3_column_bytes(this->_statement, column_index);
}

int16 sqlite_statement::i16   (word16 column_index)
{
    return (int16) sqlite3_column_bytes16(this->_statement, column_index);
}

int32 sqlite_statement::i32   (word16 column_index)
{
    return sqlite3_column_int(this->_statement, column_index);
}

int64 sqlite_statement::i64   (word16 column_index)
{
    return sqlite3_column_int64(this->_statement, column_index);
}

const char* sqlite_statement::cstr  (word16 column_index)
{
    return (const char*) sqlite3_column_text(this->_statement, column_index);
}

std::string sqlite_statement::str   (word16 column_index)
{
    return std::string((const char*)sqlite3_column_text(this->_statement, column_index));
}
//End of file
