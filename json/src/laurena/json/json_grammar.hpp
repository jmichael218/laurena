///
/// \file     json_grammar.hpp
/// \brief    Class for a JSON grammar based on Boost.spirit
/// \author   Frederic Manisse
/// \version  1.0
///
/// Class for a JSON grammar based on Boost.spirit
///
#ifndef LAURENA_JSON_SPIRIT_H
#define LAURENA_JSON_SPIRIT_H

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

#include <boost/spirit.hpp> 

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace json {


/********************************************************************************/ 
/*			grammar definition													*/ 
/********************************************************************************/ 

struct json_grammar 
  : public boost::spirit::grammar<json_grammar> 
{ 
  struct print 
  { 
    void operator()(const char *begin, const char *end) const 
    { 
      std::cout << std::string(begin, end) << std::endl; 
    } 

    void operator()(const double d) const 
    { 
      std::cout << d << std::endl; 
    } 
  }; 

  template <typename Scanner> 
  struct definition 
  { 
    boost::spirit::rule<Scanner> object, member, string, value, number, array; 

    definition(const json_grammar &self) 
    { 
      using namespace boost::spirit; 
      object = "{" >> member >> *("," >> member) >> "}"; 
      member = string[print()] >> ":" >> value; 
      string = "\"" >> *~ch_p("\"") >> "\""; 
      value = string | number | object | array | str_p("true")[print()] | "false" | "null"; 
      number = real_p[print()]; 
      array = "[" >> value >> *("," >> value) >> "]"; 
    } 

    const boost::spirit::rule<Scanner> &start() 
    { 
      return object; 
    } 
  }; 
}; 

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file