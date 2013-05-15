///
/// \file     json_lexer.hpp
/// \brief    lexer definition for the json language
/// \author   Frederic Manisse
/// \version  1.0
///
/// lexer definition for the json language
///
#ifndef LAURENA_JSON_LEXER_H
#define LAURENA_JSON_LEXER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/laurena.hpp>

#include <boost/spirit/include/lex_lexertl.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace json {

/***********************************************************************************/ 
/* Class json_lexer                                                                */ 
/***********************************************************************************/ 

template <typename LEXER>
struct json_lexer : lex::lexer<LEXER>
{
    json_lexer()
    {
        // define tokens (the regular expression to match and the corresponding
        // token id) and add them to the lexer 
        this->self.add
			(":",			TOKEN_DPOINTS)
			("=",			TOKEN_EQUAL)
			("{",			TOKEN_BRACKET_OPEN)
			("}",			TOKEN_BRACKET_CLOSE)
			("[",			TOKEN_ARRAY_BRACKET_OPEN)
			("]",			TOKEN_ARRAY_BRACKET_CLOSE)
			(",",			TOKEN_COLON)
			("[-+]?[0-9]+", TOKEN_INTEGER)
			("[-+]?[0-9]*\.?[0-9]+", TOKEN_FLOAT)
			("true",		TOKEN_TRUE)
			("false",		TOKEN_FALSE)
			("null",		TOKEN_NULL)
			("\"[^\"]*\"",	TOKEN_STRING)
			("\n",			TOKEN_EOL)
			(" \t\r",		TOKEN_TABS)
        ;
    }
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
