///
/// \file     time.hpp
/// \brief    A toolbox of functions for time related operations
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for time related operations
///

#ifndef LAURENA_TIME_H
#define LAURENA_TIME_H

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

/********************************************************************************/ 
/*              interface                                                       */ 
/********************************************************************************/ 
class Filename {
    
    public:

    //<! Extract a filename from a full path filename
    static void extractFilename(const std::string& fullpath_filename, std::string& filename) ;

    //<! Extract directory from a full path filename
    //<! The directory doesn't have a final "/"
    static void extractDirectory(const std::string& fullpath_filename, std::string& directory) ;

    //<! Extract the prefix ( the part before the .txt for example ) from a filename
    static void extractPrefix(const std::string& filename, std::string& prefix) ;

    //<! Extract the suffix ( the 'txt' part of readme.txt for example ) from a filename
    static void extractSuffix(const std::string& filename, std::string& suffix ) ;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
