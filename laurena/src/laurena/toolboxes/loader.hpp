///
/// \file     loader.hpp
/// \brief    A toolbox of functions to load file contents
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions to load file contents
///

#ifndef LAURENA_LOADER_H
#define LAURENA_LOADER_H

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
class Loader {
    
    public:


    static std::string  load(const std::string& filename);
    static std::string& load(const std::string& filename, std::string& destination); 

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
