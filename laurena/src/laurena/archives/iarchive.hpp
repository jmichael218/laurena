///
/// \file     iarchive.hpp
/// \brief    Base class for an input archive i.e a class to serialize a class from a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an input archive i.e a class to serialize a class from a file format.
///
#ifndef LAURENA_IARCHIVE_H
#define LAURENA_IARCHIVE_H

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

#include <laurena/descriptors/descriptor.hpp>
#include <laurena/parsing/tokenizer.hpp>
#include <laurena/language/language.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

class iarchive
{
public:

    /****************************************************************************/ 
    /*          constructors, destructor                                        */ 
    /****************************************************************************/ 

    //! Default constructor
    iarchive ();

    //! destructor
    virtual ~iarchive();
    
    /****************************************************************************/ 
    /*          Virtual functions to redefine for each serializer class         */ 
    /****************************************************************************/ 

    //! parse a content 
    virtual any& parse (const std::string& name, any& destination) = 0 ;
       
    //! clear variables of last parsing
    virtual iarchive& clear () ;

    /*
     * \brief return language name
     *
     * return the language tag name. It is used to build annotation name like format.json (and so language must return "json"
     */
    virtual const class language& language() const = 0;
   
    virtual void skip_tabs();

    virtual token read_token(const bitfield& allowed_tokens);

    /*
     * \brief check if the field do have a field format annotation
     *
     * Check if the field do have a field format annotation named "format." + this->language()
     * If yes, read the value in svalue and set it.
     * return false otherwhile
     */
    virtual bool read_custom_field_format(const field& f, any& object);

    /****************************************************************************/
    /*      other functions                                                     */ 
    /****************************************************************************/
    inline void         logger (std::ostream* logger)   { _logger = logger ; }
    inline tokenizer&   reader()                        { return _tokenizer ; }

    /****************************************************************************/
    /*      commun functions                                                    */ 
    /****************************************************************************/ 



    token read_token(word8 allowed_token_id);
    token read_token(word8 allowed_token1_id, word8 allowed_token2_id);
    token read_token(word8 allowed_token1_id, word8 allowed_token2_id, word8 allowed_token3_id);
    token read_token(word8 allowed_token1_id, word8 allowed_token2_id, word8 allowed_token3_id, word8 allowed_token4_id);

    /****************************************************************************/
    /*      protected datas                                                     */ 
    /****************************************************************************/ 
    protected:
    std::ostream*           _logger;
    std::string             _source_filename;
    tokenizer               _tokenizer;

};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
