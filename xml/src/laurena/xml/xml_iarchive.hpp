///
/// \file     xml_iarchive.hpp
/// \brief    Class for a XML input archive i.e a class to create/fill a class instance from a XML file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a XML input archive i.e a class to create/fill a class instance from a XML file format.
///
#ifndef LAURENA_XML_IARCHIVE_H
#define LAURENA_XML_IARCHIVE_H

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
namespace xml {

/***********************************************************************************/ 
/* Class iarchive_mdl                                                              */ 
/***********************************************************************************/ 

class iarchive_xml : public iarchive
{

    /****************************************************************************/ 
    /*              constructor, destructor                                     */ 
    /****************************************************************************/ 
public:
    iarchive_xml();
    virtual ~iarchive_xml();

    /****************************************************************************/ 
    /*          Virtual functions from IArchive                                 */ 
    /****************************************************************************/ 
    virtual any& parse (const std::string& name, any& destination) ;

    /****************************************************************************/
    /*          static functions                                                */ 
    /****************************************************************************/ 
    static any& load (const std::string& filename, const std::string& name, 
                       any& destination);

    static any& fromString (const char* source, const std::string& name, 
                       any& object);

    /****************************************************************************/
    /*          parsing sub function                                            */ 
    /****************************************************************************/ 
    public:

    void skipTabs();

    void readToken	(token& tk, boost::dynamic_bitset<>& allowed_tokens);

    void readExpected(token& tk, word8 tokenId);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3);
	void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3, word8 tokenId4);


    /****************************************************************************/ 
    /*              protected datas                                             */ 
    /****************************************************************************/ 
    protected:

    std::string     _last_keyword;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
