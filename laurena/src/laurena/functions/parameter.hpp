///
/// \file     parameter.hpp
/// \brief    A type to describe the parameter of a function/command
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A type to store a named variable of Any type
///

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef LAURENA_PARAMETER_H
#define LAURENA_PARAMETER_H

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
#include <laurena/types/variable.hpp>
#include <laurena/types/string_array.hpp>
#include <laurena/types/context.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          Parameter                                                            */ 
/*********************************************************************************/ 

class parameter 
{
public:
     

    /****************************************************************************/ 
    /*          constants                                                       */ 
    /****************************************************************************/ 
    enum FLAGS {
        FLAG_MANDATORY      = 0,
        FLAG_LINE			=1, // use full line for this argument
        MAX_FLAGS           = 2,
    };

    static const string_array FlagsKeywords;

    /****************************************************************************/ 
    /*          constructor, destructor                                         */ 
    /****************************************************************************/ 
    parameter ();

    /****************************************************************************/ 
    /*          parsing                                                         */ 
    /****************************************************************************/ 
    bool parse(any& value, std::istream& input) const;

    /****************************************************************************/ 
    /*          accessors                                                       */ 
    /****************************************************************************/
    
    inline const std::string& name () const                         { return this->_name ; }
    inline parameter&         name (const std::string& name)        { this->_name = name ; return *this ; }
    
    inline const descriptor*  desc() const                          { return this->_descriptor ; }
    inline parameter&         desc (const descriptor* d)			{ this->_descriptor = d ; return *this; }


    inline bool                     isMandatory() const             { return this->_flags.test(FLAG_MANDATORY); }
    inline parameter&               isMandatory(bool mode)          { this->_flags.set(FLAG_MANDATORY,mode); return *this; }

    inline bool                     isLine() const					{ return this->_flags.test(FLAG_LINE); }
    inline parameter&               isLine(bool mode)				{ this->_flags.set(FLAG_LINE,mode); return *this; }

    inline boost::dynamic_bitset<>& flags()                         { return _flags ; }


    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    protected:
    std::string                   _name;
    const descriptor*			  _descriptor;
    boost::dynamic_bitset<>       _flags;   
    
};

//
// syntax for a parameter array is 
// string name, string surname
// string chat_action, [FULLLINE, OPTION] text
// [] is optional. Inside are flags
// 
class parameters : public std::vector<parameter>
{
public:

    parameters();

    /****************************************************************************/ 
    /*      parsing                                                             */ 
    /****************************************************************************/ 

    bool parse (context& cnt, std::istream& input) const;
};




/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif