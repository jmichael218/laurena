///
/// \file     sql_database.hpp
/// \brief    Interface to access a database
/// \author   Frederic Manisse
/// \version  1.0
///
/// Interface to access a database
///
#ifndef LAURENA_SQL_DATABASE_H
#define LAURENA_SQL_DATABASE_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace sql {

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 

class sql_statement;

/********************************************************************************/ 
/* sql database                                                                 */ 
/********************************************************************************/ 

class sql_database
{
public:

    /****************************************************************************/
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    sql_database ();
    virtual ~sql_database () ;

    /****************************************************************************/
    /*      virtual functions                                                   */ 
    /****************************************************************************/ 
    virtual bool open    () = 0;
    virtual bool close   () = 0;

    /*
        return a column definition:
        Exemple : a field of type std::string will return "NAME           TEXT    NOT NULL" for a SQLite database
        Return "" for an unsupported type
    */ 
    virtual std::string column (const field& f) const;

    virtual std::shared_ptr<sql_statement>   query   (const std::string& str_query);
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file