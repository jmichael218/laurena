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

std::string sqlite_database::column (const field& f) const
{
    const sql_column* col = dynamic_cast<const sql_column*>(f.annotations().get(sql_column::ANNOTATION_NAME));
    if (!col) 
        return std::string("");

    std::ostringstream ss;
    ss << col->column() << " ";

    if (f.desc().name() == "string")
        ss << "TEXT" ;

    else
        return std::string("");

    if (f.is_primary_key())
    ss << " PRIMARY KEY NOT NULL";

    return ss.str();

}

std::string sqlite_database::create_table_query(const sql_dao& dao)
{
    const descriptor& desc = dao.desc();
    const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(desc.annotations().get(sql_tablename::ANNOTATION_NAME));
    const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(desc.feature(Feature::POLYMORPHIC));

    if (original_tablename == nullptr)
        return std::string("");

    std::ostringstream ss;
    ss << "CREATE TABLE " << original_tablename->name() << "(" << std::endl;

	const sql_tablename* current_table = original_tablename;
    const descriptor*    current_desc  = &desc;
	while (true)
    {


        if (!pcf->has_parent())
            break;

        current_desc = &pcf->parent();
    }

    ss << ");";

    return ss.str();
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
