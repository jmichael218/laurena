///
/// \file     parser.hpp
/// \brief    parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
///

#ifndef LAURENA_PARSER_H
#define LAURENA_PARSER_H

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

#include <laurena/parsing/token.hpp>
#include <laurena/types/charset.hpp>
#include <laurena/descriptors/classes.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              forward declaration                                             */ 
/********************************************************************************/ 
class tokenizer;

/*********************************************************************************/
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class parser
{
public:    

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const =0;
};


/********************************************************************************/ 
/*      enhanced array of parser                                                */ 
/********************************************************************************/ 

class parsers : public std::vector<parser*>
{

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
