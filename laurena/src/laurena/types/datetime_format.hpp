///
/// \file     dateformat.hpp
/// \brief    A datetime format class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   A datetime format class
///

#ifndef LAURENA_DATETIME_FORMAT_H
#define LAURENA_DATETIME_FORMAT_H

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

#include <laurena/types/string_array.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*      DateFormat class                                                        */ 
/********************************************************************************/ 

class datetime_format
{

    /****************************************************************************/ 
    /*          constructor & destructor                                        */ 
    /****************************************************************************/ 
    public:
    datetime_format () ;

    /****************************************************************************/ 
    /*          parsing  / format                                               */ 
    /****************************************************************************/ 

    word64		epoch  (const std::string& source, const std::string& format) ;
    std::string format (word64 epoch, const std::string& format) ;

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    public:    
    string_array      _months ;
    string_array      _months_abbrev ;
    string_array      _days ;
	string_array      _days_abbrev;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}   
#endif
//end of file
