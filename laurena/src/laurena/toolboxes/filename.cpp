///
/// \file     filename.cpp
/// \brief    A toolbox of functions for filenames and directory names
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for filenames and directory names
///

#include <laurena/toolboxes/filename.hpp>
#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*                      FILENAME FUNCTIONS                                      */ 
/*                                                                              */ 
/********************************************************************************/ 

//<! Extract a filename from a full path filename
void Filename::extractFilename(const std::string& fullpath_filename, std::string& filename)
{
    int32 pos = fullpath_filename.find_last_of(const_charsets<>::FULLPATH_FILENAME_SEPARATOR.characters());

    if ( pos == -1 ) 
        filename = fullpath_filename ;    
    else 
    {
        pos++ ; // to skip the / character
        filename = fullpath_filename.substr(pos) ;
    }

}

//<! Extract directory from a full path filename
//<! The directory doesn't have a final "/"
void Filename::extractDirectory(const std::string& fullpath_filename, std::string& directory)
{
    int32 pos = fullpath_filename.find_last_of(const_charsets<>::FULLPATH_FILENAME_SEPARATOR.characters()) ;
    if ( pos == -1 ) 
        directory = "" ;
    else 
        directory = fullpath_filename.substr(0,pos) ;
}


//<! Extract the prefix ( the part before the .txt for example ) from a filename
void Filename::extractPrefix(const std::string& filename, std::string& prefix)
{
    int32 pos = filename.find_last_of(".") ;
    if ( pos == -1 ) 
        prefix = filename ;
    else 
        prefix = filename.substr (0,pos) ;    
}

//<! Extract the suffix ( the 'txt' part of readme.txt for example ) from a filename
void Filename::extractSuffix(const std::string& filename, std::string& suffix )
{
    int32 pos = filename.find_last_of(".") ;
    if ( pos == -1 ) 
        suffix = "" ;
    else
    {
        pos ++ ;
        suffix = filename.substr(pos,filename.length()-pos) ;
    }
}

//End of file
