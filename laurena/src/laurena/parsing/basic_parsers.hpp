///
/// \file     basic_parsers.hpp
/// \brief    parsers for basic types and formats
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parsers for basic types and formats
///

#ifndef LAURENA_BASIC_PARSERS_H
#define LAURENA_BASIC_PARSERS_H

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
#include <laurena/parsing/parser.hpp>
#include <laurena/parsing/tokenizer.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/*********************************************************************************/
/*          basic parsers                                                        */ 
/*********************************************************************************/ 


template<typename T>
class generic_parser : public parser
{
    //! a tokenizer is providing a list of tokens from a source code.
    virtual bool read (tokenizer& tk, any& value, bool consume) const  
    {
        T* t = anycast<T*>(value);

        tokenizer::state s = tk.current();

        try 
        {        
            tk >> *t ;
            if (!consume)
                tk.restore(s);

            return true;
        } 
        catch (exception& ) 
        {
            tk.restore(s);
            return false;
        }
        
    }

};

/********************************************************************************/ 
/*                                                                              */ 
/*          read an expected single character                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
class single_character_parser : public parser
{
public:

    single_character_parser (word8 character);
    virtual ~single_character_parser();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:
    word8           _character;
};

/********************************************************************************/ 
/*                                                                              */ 
/*          read an expected keyword                                            */ 
/*                                                                              */ 
/********************************************************************************/ 
class keyword_parser : public parser
{
public:

    keyword_parser(const char* keyword);
    virtual ~keyword_parser ();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:
    std::string         _keyword;
};

/********************************************************************************/ 
/*                                                                              */ 
/*          read an integer with optional signed character + or -               */ 
/*                                                                              */ 
/********************************************************************************/ 
class signed_integer_parser : public parser
{
public:

    signed_integer_parser();
    virtual ~signed_integer_parser();
    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:
};

/********************************************************************************/ 
/*                                                                              */ 
/*         read hexadecimal numbers                                             */ 
/*                                                                              */ 
/********************************************************************************/ 
class hexadecimal_parser : public parser
{
public:

    hexadecimal_parser();
    virtual ~hexadecimal_parser();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:

};

/********************************************************************************/ 
/*                                                                              */ 
/*          single string reader ( quoted with " " )                            */ 
/*                                                                              */ 
/********************************************************************************/ 
class string_parser : public parser
{
public:

    string_parser();
    virtual ~string_parser ();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

};

/********************************************************************************/ 
/*                                                                              */ 
/*          multiline string reader ( quoted with " " )                         */ 
/*                                                                              */ 
/********************************************************************************/ 
class multi_string_parser : public parser
{
public:

    multi_string_parser();
    virtual ~multi_string_parser ();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:

};

/********************************************************************************/ 
/*                                                                              */ 
/*          read EOL                                                            */ 
/*                                                                              */ 
/********************************************************************************/ 
class eol_parser : public parser
{
public:

    eol_parser();
    virtual ~eol_parser ();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:

};

/********************************************************************************/ 
/*                                                                              */ 
/*          read Tabs                                                           */ 
/*                                                                              */ 
/********************************************************************************/ 
class tabs_parser : public parser
{
public:

    tabs_parser();
    virtual ~tabs_parser ();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:

};


/********************************************************************************/ 
/*                                                                              */ 
/*          accept any length belonging to a charset                            */ 
/*                                                                              */ 
/********************************************************************************/ 
class charset_parser : public parser
{
public:

    charset_parser(const charset& characters, bool until=false);
    virtual ~charset_parser();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:
    const charset&            _charset;    
    bool                      _until ;


};



/********************************************************************************/ 
/*                                                                              */ 
/*              accept any character but a given length                         */ 
/*                                                                              */ 
/********************************************************************************/ 
class length_parser : public parser
{
public:

    length_parser(word32 length=1);
    virtual ~length_parser();

    virtual bool read (tokenizer& tokenizer, any& value, bool consume) const;

    protected:

    word32  _length;


};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
