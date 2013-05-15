///
/// \file     writer.hpp
/// \brief    writer classes are optional output writer for a type, like hexadecimal output for an integer ...
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// formatter classes are optional output writer for a type, like hexadecimal output for an integer ...
///

#ifndef LAURENA_WRITER_H
#define LAURENA_WRITER_H

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

/*********************************************************************************/
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class writer
{
public:    

    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool write (std::ostream& output, any& value) const =0;
};

//! A generic writer assuming ostream << T is defined.
template<typename T>
class generic_writer : public writer
{

    virtual bool write (std::ostream& output, any& value) const
    {
        output <<  *(anycast<T*>(value));
        return true;
         
    }
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
