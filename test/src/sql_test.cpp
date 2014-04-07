///
/// \file     sql_test.cpp
/// \brief    Test Sql serialization
/// \author   Frederic Manisse
/// \version  1.0
///
/// Test Sql serialization
//
#include <laurena/laurena.hpp>
#include <laurena/sql/sql.hpp>
#include "character.hpp"

#include <laurena/sql/sqlite/sqlite_database.hpp>

using namespace laurena;
using namespace test;

void test_dao ()
{
	const descriptor* desc = classes::by_name("character");
	assert(desc);

	character bob;
	bob._name = "Bob Smith";
	bob._age  = 42;

	sql::sql_dao d;
	any key ( "Bob Smith");
	std::string sInsertQuery = d.generateInsertStatement (*desc, bob);
	std::string sSelectQuery = d.generateSelectByPrimaryKey(*desc, key);

	testunit::log() << "insert query = " << sInsertQuery << std::endl;
	testunit::log() << "select query = " << sSelectQuery << std::endl;

	return;
}


void test_sqlite()
{
    sql::sqlite_database db ("datas/test");

	const descriptor* desc = classes::by_name("character");
	assert(desc);

	character bob;
	bob._name = "Bob Smith";
	bob._age  = 42;

	sql::sql_dao d;
	any key ( "Bob Smith");
	std::string sInsertQuery = d.generateInsertStatement (*desc, bob);

    std::shared_ptr<sql::sql_statement> st = db.query(sInsertQuery);

    st = nullptr;
    db.close();
    return;
    
}

void test_sql()
{
	//sql::query q = sql::select ( field0, field1, sql::max(field3)) << sql::from ( descriptor ) << sql::where ( field (0) , sql::equals , 'XXXX');

	test_dao();
    test_sqlite();

    return;
}