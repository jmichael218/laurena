///
/// \file     oarchive_json.hpp
/// \brief    Class for a json output archive i.e a class to serialize a class into the JSON file format.
/// \author   Frederic Manisse
/// \version  1.0
///
/// Class for a json output archive i.e a class to serialize a class into the JSON file format.
///
#ifndef LAURENA_OARCHIVE_JSON_H
#define LAURENA_OARCHIVE_JSON_H

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

/*********************************************************************************/
/*          base class for output archives                                       */ 
/*********************************************************************************/ 

class oarchive_json : public oarchive{

    public:   
    oarchive_json () ;
    virtual ~oarchive_json ();


    /****************************************************************************/ 
    /*          Virtual class to redefine for each serializer class             */ 
    /****************************************************************************/ 

    virtual oarchive& serialize(const std::string& name, const any& value,bool injection=false);
    
    /****************************************************************************/ 
    /*              new functions                                               */ 
    /****************************************************************************/ 

	void serializeObject(const any& value);

    void serializeElements(const descriptor& cd, const any& value);

	inline oarchive_json& compact (bool mode) { this->_compact = mode; return *this; }

    protected:
    void completeLastLine();
	void printFieldName(const field& f);

    void serializeFields(const descriptor& cd, const any& value);

    /****************************************************************************/ 
    /*      protected function                                                  */ 
    /****************************************************************************/ 
    protected:
    tab						_tab;
    bool					_compact ;
    const archive_format*   _format;
    word16					_nb_fields;         // nb of serialized fields in a level
	word32					_depth;
    
        
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file
