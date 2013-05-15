///
/// \file     variable.hpp
/// \brief    A type to store a named variable of any type
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A type to store a named variable of Any type
///

#ifndef LAURENA_VARIABLE_H
#define LAURENA_VARIABLE_H

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

#include <laurena/types/any.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          class variable                                                       */ 
/*********************************************************************************/ 

class variable 
{
public:
     
    /****************************************************************************/ 
    /*          constructors                                                    */ 
    /****************************************************************************/ 
    variable ();
    variable (const variable& source);
    variable (const std::string& name, const any& value);

    virtual ~variable ();

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    any             _value;
    std::string     _name;
    
};


/*********************************************************************************/
/*          class variable_list                                                  */ 
/*********************************************************************************/ 

class variable_list : public std::list<variable>
{
public:

    /****************************************************************************/ 
    /*          constructors & destructors                                      */ 
    /****************************************************************************/ 
 
    variable_list() ;
    virtual ~variable_list ();

    /****************************************************************************/ 
    /*          functions                                                       */ 
    /****************************************************************************/ 
    variable*   find(const std::string& name);
    variable_list& add (const std::string& name, const any& value);
};



/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif