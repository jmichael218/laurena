///
/// \file     sql_database.cpp
/// \brief    Interface to access a database
/// \author   Frederic Manisse
/// \version  1.0
///
/// Interface to access a database
///
#include <laurena/sql/sql_database.hpp>
#include <laurena/sql/sql_statement.hpp>

using namespace laurena;
using namespace sql;

sql_database::sql_database () 
{ }

sql_database::~sql_database () 
{ }

std::shared_ptr<sql_statement>   sql_database::query   (const std::string& str_query)
{
    return std::make_shared<sql_statement>(*this, str_query);
}

std::string sql_database::column (const field& f) const
{
    return std::string("");
}

//End of file
