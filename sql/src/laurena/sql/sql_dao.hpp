///
/// \file     sql_dao.hpp
/// \brief    DAO base class and templated class
/// \author   Frederic Manisse
/// \version  1.0
///
/// Annotations for sql persistance
///
#ifndef LAURENA_SQL_DAO_H
#define LAURENA_SQL_DAO_H

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
/* sql dao                                                                      */ 
/********************************************************************************/ 

class sql_dao : public dao
{
public:

    /****************************************************************************/ 
    /*          destructor, constructors                                        */ 
    /****************************************************************************/ 
    sql_dao(const descriptor& desc, sql_database& db, const std::string& tablename); 
    virtual ~sql_dao();

    /****************************************************************************/ 
    /*          virtual functions                                               */ 
    /****************************************************************************/ 
    virtual any&    read    (const any& primaryKey, any& destination);

    virtual any&    create  (any& object);
    virtual any&    update  (any& object);
    virtual void    erase   (any& object);
    virtual void    erase   (const any& primaryKey);

    virtual bool    exist   (const any& primaryKey);

    /****************************************************************************/ 
    /*          new functions                                                   */ 
    /****************************************************************************/ 
    std::string create_table_query();
	std::string insert_query(const any& object);
	std::string select_by_primary_key_query(any& primary_key);
	std::string delete_by_primary_key_query(any& primary_key);

    /****************************************************************************/ 
    /*          members datas                                                   */ 
    /****************************************************************************/ 
    protected:

    std::string         _tablename;
    sql_database&       _db;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file