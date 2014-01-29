///
/// \file     json_dao.hpp
/// \brief    dao for a json file based persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// dao for a json file based persistance
///
#ifndef LAURENA_JSON_DAO_H
#define LAURENA_JSON_DAO_H

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
namespace json {

/***********************************************************************************/ 
/* Class json_dao                                                                  */ 
/***********************************************************************************/ 

class json_dao : public file_dao
{
public:

    /****************************************************************************/ 
    /*          typedef                                                         */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<json_dao>       sptr;

    /****************************************************************************/ 
    /*          destructor, constructors                                        */ 
    /****************************************************************************/ 
    json_dao (const descriptor& desc, const std::string& directory);
    virtual ~json_dao();

    /****************************************************************************/ 
    /*          new virtual functions                                           */ 
    /****************************************************************************/ 
    // return file extension
    virtual const std::string&          extension ();
    virtual std::shared_ptr<oarchive>   formatter ();
    virtual std::shared_ptr<iarchive>   parser    ();
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file