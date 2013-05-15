///
/// \file       string_array.hpp
/// \brief      A vector<string> container with enhanced methods.
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A vector<string> container with enhanced methods.
///

#ifndef LAURENA_STRING_ARRAY_H
#define LAURENA_STRING_ARRAY_H

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
/*          string_array                                                          */ 
/*********************************************************************************/ 

class string_array : public std::vector<std::string> 
{
public:

    /****************************************************************************/ 
    /*              constructors, destructor                                    */ 
    /****************************************************************************/ 
    string_array ();
    string_array (const char* value, unsigned char separator = ' ');
    string_array (const string_array& object);
    virtual ~string_array () {}

    /****************************************************************************/ 
    /*              new functions                                               */ 
    /****************************************************************************/ 
    ///
    /// \brief find without lower/upper case difference
    int32   find(const std::string& value) const;    

    ///
    /// \brief find exact value
    /// 
    int32   findExact(const std::string& value) const;


    void set(const char* keywordList, word8 separator=' ');
    inline void set(const std::string& keywordList, word8 separator=' ') {     this->set(keywordList.c_str(),separator); }
    
    void all (const std::string& value);

    inline const string_array* attributes() const 
            { return this->_attributes ; }

    void attributes(const string_array* attributesArray);

    std::string concat(const std::string& delimiter) const;

    /****************************************************************************/ 
    /*              protected datas                                             */ 
    /****************************************************************************/ 
    protected:

    const string_array*        _attributes;
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif