///
/// \file     loader.cpp
/// \brief    A toolbox of functions to load file contents
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions to load file contents
///

#include <laurena/toolboxes/loader.hpp>
#include <laurena/exceptions/file_not_found_exception.hpp>

using namespace laurena;

std::string Loader::load(const std::string& filename)
{
    std::string str;
    return std::string(Loader::load(filename,str));
}

std::string& Loader::load(const std::string& filename, std::string& destination)
{
FILE * F = fopen ( filename.c_str() , "rb" ) ;

    if (!F) 
        throw LAURENA_FILE_NOT_FOUND_EXCEPTION("In Loader::load, file not found.",filename);
    
    /* get file size */ 
    fseek(F,0,SEEK_END);
    word32 sizefile = ftell ( F ) ;

    // handle file of size 0
    if ( sizefile == 0 )
    {
        fclose (F) ;
        destination.clear();
        return destination ;
    }

    /* create and read buffer */ 
    char* res = new char[sizefile+1];

    fseek(F,0,SEEK_SET);
    fread ( res , sizefile , 1 , F ) ;       
    res [ sizefile ] = 0 ;

    /* close file - don't need it anymore */ 
    fclose ( F ) ; 
    destination = res ;
    delete[] res;

    return destination;
}
//End of file
