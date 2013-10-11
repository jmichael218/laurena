///
/// \file     file_location.hpp
/// \brief    A location in a file ( filename, column, line )
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A location in a file ( filename, column, line )
///

#ifdef LAURENA_FILE_LOCATION_H
#define LAURENA_FILE_LOCATION_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          file_location                                                        */ 
/*********************************************************************************/ 

class file_location
{
public:

    file_location();
    file_location(const char* filename);
    file_location(const std::string& filename);

    /****************************************************************************/
    /*          functions                                                       */ 
    /****************************************************************************/ 
    void reset   ();

    void process (const char character);
    void process (const word8 character);
    void process (const char* ptr);
    void process (const char* ptr, word32 size);
    void process (const std::string& content);

    inline const std::string& filename()  const                      { return _filename ; }
    inline void               filename(const std::string& filename)  { this->_filename = filename ; }
    inline void               filename(const char* filename)         { this->_filename = filename ; }

    inline word32             column  () const                       { return _column ; }
    inline word32             line    () const                       { return _line ; }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
        
    std::string         _filename;
    word32              _column;
    word32              _line;

};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
