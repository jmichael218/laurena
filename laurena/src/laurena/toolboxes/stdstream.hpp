///
/// \file     stdstream.hpp
/// \brief    A toolbox of functions on std::istream and std::ostream classes
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A toolbox of functions on std::istream and std::ostream classes

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef LAURENA_TOOLBOX_STDSTREAM_H
#define LAURENA_TOOLBOX_STDSTREAM_H

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/types/charset.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              interface                                                       */ 
/********************************************************************************/ 
class Stream {
    
    public:

    static word32 skipWhile(std::istream& stream, const charset<>& characters);
	static word32 skipUntil(std::istream& stream, const charset<>& characters);

    static word32 readWhile(std::istream& stream, const charset<>& characters, std::string& destination);
  
    static word32 readUntil(std::istream& stream, const charset<>& characters, std::string& destination); 
    static word32 readUntil(std::istream& stream, const word8 symbol, std::string& destination); 



    static bool   expect(std::istream& stream, const char* expected);

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
