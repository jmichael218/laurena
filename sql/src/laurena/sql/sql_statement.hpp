///
/// \file     sql_statement.hpp
/// \brief    interface to a statement
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to a statement
///
#ifndef LAURENA_SQL_STATEMENT_H
#define LAURENA_SQL_STATEMENT_H

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
#include <laurena/sql/sql_database.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace sql {

/********************************************************************************/ 
/*          class query                                                         */ 
/********************************************************************************/ 

class sql_statement 
{
    /****************************************************************************/
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    public:
    sql_statement(sql_database& db, const std::string& query);
    virtual ~sql_statement();


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
    /*          member datas                                                    */ 
    /****************************************************************************/
    protected:

    sql_database&       _db;
    std::string         _query;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
