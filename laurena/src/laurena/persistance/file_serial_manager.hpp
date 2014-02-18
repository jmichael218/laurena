///
/// \file     file_serial_manager.hpp
/// \brief    A file based manager for a table of serial ID
/// \author   Frederic Manisse
/// \version  1.0
///
/// A file based manager for a table of serial ID
///
#ifndef LAURENA_FILE_SERIAL_MANAGER_H
#define LAURENA_FILE_SERIAL_MANAGER_H

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

#include <laurena/persistance/serial_manager.hpp>
#include <laurena/persistance/persistance.hpp>
#include <laurena/language/language.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*     file_serial_manager                                                      */ 
/********************************************************************************/ 

class file_serial_manager : public serial_manager
{
    public:

    /****************************************************************************/ 
    /*      constructors, destructor                                            */ 
    /****************************************************************************/     
    file_serial_manager(persistance& engine, const std::string& spipeline, language& fileformat, const std::string& directory);
    file_serial_manager(persistance& engine, const char* spipeline, language& fileformat, const char* directory);

    virtual ~file_serial_manager();

    /****************************************************************************/ 
    /*      virtual functions implementation                                    */ 
    /****************************************************************************/ 
    virtual void    create(any object)                              ;
    virtual void    read  (const any& serialKey, any destination)   ;
    virtual bool    exist (const any& serialKey)                    ;
    virtual bool    remove(const any& serialKey)                    ;

    /****************************************************************************/ 
    /*      new functions                                                       */ 
    /****************************************************************************/ 

    std::string filename(const any& serialKey);

    /****************************************************************************/ 
    /*      datas                                                               */ 
    /****************************************************************************/   
    protected:
    std::string         _directory;
    language&     _language;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file