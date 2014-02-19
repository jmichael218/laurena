///
/// \file     unique.hpp
/// \brief    A base type to be used as base class for classes bases on the same serial table
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A base type to be used as base class for classes bases on the same serial table
///

#ifndef LAURENA_UNIQUE_H
#define LAURENA_UNIQUE_H

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
/*          class unique                                                         */ 
/*********************************************************************************/ 

class unique 
{
public:

    /****************************************************************************/ 
    /*      typedefs                                                            */ 
    /****************************************************************************/ 
    typedef std::shared_ptr<unique>             sptr;
    typedef std::weak_ptr<unique>               wptr;

    /****************************************************************************/ 
    /*      constants                                                           */ 
    /****************************************************************************/ 
    static const word64 UNDEFINED_SERIAL = 0;

    /****************************************************************************/ 
    /*      constructors, destructor                                            */ 
    /****************************************************************************/ 
    unique ();
    unique (word64 serial);
    unique (const unique& u);
    unique (      unique&& u);

    virtual ~unique();

    /****************************************************************************/ 
    /*      accesseurs                                                          */ 
    /****************************************************************************/ 
    word64 serial() const;
    void   serial(word64 value);

    sptr   owner();
    void   owner(word64 owner_serial);
    void   owner(unique::sptr& ptr);

    /****************************************************************************/ 
    /*      datas                                                               */ 
    /****************************************************************************/ 
    private:
    word64          _serial;
    word64          _owner_serial;
    wptr            _owner;
};

/********************************************************************************/ 
/*          inline functions                                                    */ 
/********************************************************************************/ 

inline
word64 unique::serial() const
{ return this->_serial; }

inline
void unique::serial(word64 value)
{ this->_serial = value; }

inline
unique::sptr unique::owner()
{ return this->_owner.lock(); }

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif