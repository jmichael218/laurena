///
/// \file     iarchive_json.hpp
/// \brief    Class for a JSON input archive i.e a class to serialize a class from a JSON file format.
/// \author   Frederic Manisse
/// \version  1.0
///
/// Class for a JSON input archive i.e a class to serialize a class from a JSON file format.
///
#ifndef LAURENA_IARCHIVE_JSON_H
#define LAURENA_IARCHIVE_JSON_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace json {

/***********************************************************************************/ 
/* Class IArchive                                                                  */ 
/***********************************************************************************/ 

class iarchive_json : public iarchive
{

    /****************************************************************************/ 
    /*              cosntructor, destructor                                     */ 
    /****************************************************************************/ 
public:
    iarchive_json();
    virtual ~iarchive_json();

    /****************************************************************************/ 
    /*          Virtual functions from IArchive                                 */ 
    /****************************************************************************/ 
    virtual any& parse (const std::string& name, any& destination) ;

    /****************************************************************************/
    /*          parsing sub function                                            */ 
    /****************************************************************************/ 

	/****************************************************************************/ 
	/*		protected functions for parsing part of json						*/ 
	/****************************************************************************/ 
	protected:
	void readToken(token& tk, boost::dynamic_bitset<>& allowed_tokens);
	bool readMaybeToken (token& tk, boost::dynamic_bitset<>& allowed_tokens);

    void readExpected(token& tk, word8 tokenId);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3);
	void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3, word8 tokenId4);

	bool readMaybe(token& token, word8 tokenId1, word8 tokenId2, word8 tokenId3);

	void parseObject(any& destination);
	void parseElements(any& object);
	void parseValue(any& object,const field* fdesc = nullptr);


    /****************************************************************************/ 
    /*              protected datas                                             */ 
    /****************************************************************************/ 
    protected:

    std::string     _last_keyword;

	word32			_depth ;
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
