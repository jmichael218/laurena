///
/// \file     tab.hpp
/// \brief    This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
///

#ifndef LAURENA_TAB_H
#define LAURENA_TAB_H

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
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class tab
{
public:    
    
    /****************************************************************************/
    /*      constants                                                           */ 
    /****************************************************************************/ 
    tab (const std::string& sequence, word16 initial_length = 0);

    /****************************************************************************/ 
    /*      operations                                                          */ 
    /****************************************************************************/ 
    tab& decrease ();
    tab& increase ();
    inline const std::string& str() const    { return this->_tab ; }
    

    /****************************************************************************/ 
    /*      protected member data                                               */ 
    /****************************************************************************/ 
    protected:

    std::string     _sequence ;       // tab sequence. Can be '\t' or '    ' or whatever
    word16          _tab_length;      // how many tab characters must be inserted   
    std::string     _tab;             // the tab string.

};

/********************************************************************************/ 
/*          other functions                                                     */ 
/********************************************************************************/ 
inline std::ostream& operator << (std::ostream& dest, const tab& t)
{
    return dest << t.str();
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 


}
#endif
//End of file
