///
/// \file     charset.hpp
/// \brief    A dynamic_bitset boost set of bits enhanced to hold mask for character sets
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A dynamic_bitset boost set of bits enhanced to hold mask for character sets
///

#ifndef LAURENA_CHARSET_H
#define LAURENA_CHARSET_H

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
/*          CharSet                                                              */ 
/*********************************************************************************/ 

class charset : public boost::dynamic_bitset<>
{
public:

    charset ();
    charset (const char* characters);
    charset (const std::string& characters);
    virtual ~charset() {}
    

    inline const std::string& characters () { return _characters ; }

    /****************************************************************************/
    /*          functions                                                       */ 
    /****************************************************************************/ 
    bool validate(const char* source, word32 size = ULONG_MAX) const;
    bool validate(const word8* source, word32 size = ULONG_MAX) const;
    bool validate(const std::string& source) const;

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
        
    std::string _characters;

};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
