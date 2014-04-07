///
/// \file     sqlite_database.cpp
/// \brief    SQLite implementation of class sql_database
/// \author   Frederic Manisse
/// \version  1.0
///
/// SQLite implementation of class sql_database
///
#include <laurena/sql/sqlite/sqlite_database.hpp>
#include <laurena/sql/sqlite/sqlite_statement.hpp>

using namespace laurena;
using namespace sql;

sqlite_database::sqlite_database (const std::string& filename) : sql_database (), _db(nullptr)
{

}

sqlite_database::~sqlite_database ()
{ 
    if (this->_db != nullptr)
    {
        this->close();
        this->_db = nullptr;
    }

}


bool sqlite_database::open    ()
{
    int rc = sqlite3_open(this->_filename.c_str(), &this->_db);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(this->_db);
        this->_db = nullptr;
        return false;
    }
    return true;
}

bool sqlite_database::close   ()
{
    if (this->_db != nullptr)
    {
        sqlite3_close(this->_db);
        this->_db = nullptr;
        return true;
    }
    return false;
}

std::shared_ptr<sql_statement>   sqlite_database::query   (const std::string& str_query)
{
    if (!this->_db)
    {
        if (!this->open())
            return nullptr;
    }

    sqlite3_stmt* statement;
    const char* tail;

    if (sqlite3_prepare(this->_db, str_query.c_str(), str_query.length(), &statement, &tail) == SQLITE_OK)
    {
        int rc = sqlite3_step(statement);
        if ( rc == SQLITE_DONE || rc == SQLITE_ROW )
        {
            std::shared_ptr<sql_statement> ret = std::make_shared<sqlite_statement>(*this, statement, str_query);
            sqlite_statement* ss = (sqlite_statement*) ret.get();
            ss->_last_step_result = rc ;
            return ret;
        }
    }
    return nullptr;
}

//End of file
