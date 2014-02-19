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
    file_serial_manager(const std::string& spipeline, language& fileformat, const std::string& directory);
    file_serial_manager(const char* spipeline, language& fileformat, const char* directory);

    virtual ~file_serial_manager();

    /****************************************************************************/ 
    /*      virtual functions implementation                                    */ 
    /****************************************************************************/ 
    virtual void    create(const serial_entry& entry)        ;

    virtual void    read  (serial_entry& destination, const std::string& serialKey)                    ;
    virtual bool    exist (const std::string& serialKey)                    ;
    virtual bool    remove(const std::string& serialKey)                    ;

    /****************************************************************************/ 
    /*      new functions                                                       */ 
    /****************************************************************************/ 

    std::string filename(const std::string& serialKey) const;

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