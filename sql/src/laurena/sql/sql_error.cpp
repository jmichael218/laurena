///
/// \file     sql_error.cpp
/// \brief    Toolbox of functions to generate errors
/// \author   Frederic Manisse
/// \version  1.0
///
/// Toolbox of functions for sql persistance
///
#include <laurena/sql/sql_error.hpp>

using namespace laurena;
using namespace sql;

void sql_error::noPrimaryKey(const descriptor& desc)
{
std::string message ("class ");

	message += desc.name();
	message += " has no defined primary key sql column";
	throw LAURENA_EXCEPTION(message);
	
}

void sql_error::columnButNoTablename(const field& f)
{
std::string message ("in class ");

	message += f.desc().name();
	message +=", you are trying to add a sql_column annotation on field ";
	message += f.name();
	message += " before defining a sql_tablename annotation.";
	throw LAURENA_EXCEPTION(message);
}

void sql_error::twoPrimaryKeys(const descriptor& desc)
{
std::string message ("in class ");

	message += desc.name();
	message += " you are trying to define two (or more) primary_keys on a single table." ;
	throw LAURENA_EXCEPTION(message);
}

void sql_error::noTablename(const descriptor& desc)
{
std::string message ("in class ");

	message += desc.name();
	message += " a sql_tablename annotation must be defined." ;
	throw LAURENA_EXCEPTION(message);
}
//End of file
