///
/// \file     iarchive_mdl.hpp
/// \brief    Class for a MDL input archive i.e a class to serialize a class from a MDL file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Class for a MDL input archive i.e a class to serialize a class from a MDL file format.
///
#ifndef LAURENA_IARCHIVE_MDL_H
#define LAURENA_IARCHIVE_MDL_H

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
namespace mdl {

/***********************************************************************************/ 
/* Class iarchive_mdl                                                              */ 
/***********************************************************************************/ 

class iarchive_mdl : public iarchive
{

    /****************************************************************************/ 
    /*              cosntructor, destructor                                     */ 
    /****************************************************************************/ 
public:
    iarchive_mdl();
    virtual ~iarchive_mdl();

    /****************************************************************************/ 
    /*          Virtual functions from IArchive                                 */ 
    /****************************************************************************/ 
    virtual any& parse (const std::string& name, any& destination) ;

    /****************************************************************************/
    /*          static functions                                                */ 
    /****************************************************************************/ 
    static any& load (const char* filename, const std::string& name, 
                       any& destination);

    static any& fromString (const char* source, const std::string& name, 
                       any& object);

    /****************************************************************************/
    /*          parsing sub function                                            */ 
    /****************************************************************************/ 
    public:


    void readToken	(token& tk, boost::dynamic_bitset<>& allowed_tokens);

    void readExpected(token& tk, word8 tokenId);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2);
    void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3);
	void readExpected(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3, word8 tokenId4);



    void readChildObject        (const descriptor& d, any& parent , bool obj_is_parent );
    void readObjectContent      (const descriptor& d, any& object );
    void readDirective          (const descriptor& d, any& object );
    void readAttribute          (const descriptor& d, any& object,const std::string& attribute);
    void readInjection          (const descriptor& d, any& object, const std::string& attribute);

    //! Read value of a class field
    void readField              (const field& f, any& object);

    //! Read value of a container element
    void readElement                 (const container_feature* cf, const std::string& keyname, any& object);

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
