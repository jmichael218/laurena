///
/// \file     file_dao.hpp
/// \brief    DAO base class for file based DAO
/// \author   Frederic Manisse
/// \version  1.0
///
/// DAO base class and templated class
///
#ifndef LAURENA_FILES_DAO_H
#define LAURENA_FILES_DAO_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
#include <laurena/traits/laurena_traits.hpp>
#include <laurena/persistance/dao.hpp>
#include <laurena/archives/oarchive.hpp>
#include <laurena/archives/iarchive.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*     dao                                                                      */ 
/********************************************************************************/ 

class file_dao : public dao
{
public:

    /****************************************************************************/ 
    /*          typedef                                                         */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<file_dao>       sptr;

    /****************************************************************************/ 
    /*          destructor, constructors                                        */ 
    /****************************************************************************/ 
    file_dao (const descriptor& desc, const std::string& directory);
    virtual ~file_dao();

    /****************************************************************************/ 
    /*          virtual functions from dao                                      */ 
    /****************************************************************************/ 
    virtual any&    read    (const any& primaryKey, any& destination);
    virtual any&    create  (any& object);
    virtual any&    update  (any& object);
    virtual void    erase   (any& object);
    virtual void    erase   (const any& primaryKey);
    virtual bool    exist   (const any& primaryKey);

    /****************************************************************************/ 
    /*          new virtual functions                                           */ 
    /****************************************************************************/ 
    // return file extension
    virtual const std::string&          extension ()  =0;
    virtual std::shared_ptr<oarchive>   formatter ()  =0;
    virtual std::shared_ptr<iarchive>   parser    ()  =0;

    /****************************************************************************/ 
    /*          new functions                                                   */ 
    /****************************************************************************/ 
    std::string filename(const std::string& key);
    std::string directory(const std::string& key);
    std::string path(const std::string& key);

    //<! Create path if needed from directory
    void        createPath(const std::string& relativePath);

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    std::string       _directory;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file