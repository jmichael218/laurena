///
/// \file     token.hpp
/// \brief    An extension of any to store token information in parsing process
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An extension of any to store token information in parsing process
///

#ifndef LAURENA_TOKEN_H
#define LAURENA_TOKEN_H

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

#include <laurena/descriptors/classes.hpp>
#include <laurena/types/any.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          Token                                                                */ 
/*********************************************************************************/ 

class token : public any
{
public:

    token ();   

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    int32      _token_id;
    
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif