///
/// \file     sqlite_database.hpp
/// \brief    SQLite implementation of class sql_database
/// \author   Frederic Manisse
/// \version  1.0
///
/// SQLite implementation of class sql_database
///
#ifndef LAURENA_SQLITE_INTERFACE_H
#define LAURENA_SQLITE_INTERFACE_H

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
/* sql database                                                                 */ 
/********************************************************************************/ 

class sqlite_database : public sql_database
{
public:

    /****************************************************************************/
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    sqlite_database (const std::string& filename);
    virtual ~sqlite_database ();

    /****************************************************************************/
    /*      virtual functions                                                   */ 
    /****************************************************************************/ 
    virtual bool open    ();
    virtual bool close   ();
    virtual std::string column (const field& f) const;
    virtual std::string create_table_query(const sql_dao& dao);
    virtual std::shared_ptr<sql_statement>   query   (const std::string& str_query);

    /****************************************************************************/
    /*      members datas                                                       */ 
    /****************************************************************************/ 
    protected:

    std::string         _filename;
    sqlite3*            _db;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file