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

using namespace laurena;
using namespace test;

void test_dao ()
{
	const descriptor* desc = classes::byName("character");
	assert(desc);

	character bob;
	bob._name = "Bob Smith";
	bob._age  = 42;

	sql::dao d;
	any key ( "Bob Smith");
	std::string sInsertQuery = d.generateInsertStatement (*desc, bob);
	std::string sSelectQuery = d.generateSelectByPrimaryKey(*desc, key);

	testunit::log() << "insert query = " << sInsertQuery << std::endl;
	testunit::log() << "select query = " << sSelectQuery << std::endl;

	return;
}


void test_sql()
{
	test_dao();
}