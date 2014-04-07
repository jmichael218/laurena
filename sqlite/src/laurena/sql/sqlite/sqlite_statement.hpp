///
/// \file     sqlite_statement.hpp
/// \brief    SQLite implementation of class sql_statement
/// \author   Frederic Manisse
/// \version  1.0
///
/// SQLite implementation of class sql_statement
///
#ifndef LAURENA_SQLITE_STATEMENT_H
#define LAURENA_SQLITE_STATEMENT_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>
#include <laurena/sql/sql.hpp>
#include <laurena/sql/sqlite/sqlite3.h>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace sql {

/********************************************************************************/ 
/*              forward declaration                                             */ 
/********************************************************************************/ 

class sqlite_database;

/********************************************************************************/ 
/* sql database                                                                 */ 
/********************************************************************************/ 

class sqlite_statement : public sql_statement
{
public:

    /****************************************************************************/
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    sqlite_statement (sql_database& db, sqlite3_stmt* statement, const std::string& query);
    virtual ~sqlite_statement ();

    /****************************************************************************/
    /*      virtual functions                                                   */ 
    /****************************************************************************/ 
    virtual bool has_data();

    virtual int8        i8    (word16 column_index);
    virtual int16       i16   (word16 column_index);
    virtual int32       i32   (word16 column_index);
    virtual int64       i64   (word16 column_index);
    virtual const char* cstr  (word16 column_index);
    virtual std::string str   (word16 column_index);

    /****************************************************************************/
    /*      members datas                                                       */ 
    /****************************************************************************/ 
    protected:

    sqlite3_stmt*       _statement;
    int                 _last_step_result;

    friend class sqlite_database;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file