///
/// \file     json_interface.hpp
/// \brief    interface to mask internal calls to serialize from/to json
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to json
///
#ifndef LAURENA_INTERFACE_JSON_H
#define LAURENA_INTERFACE_JSON_H

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
/* json interface                                                                  */ 
/***********************************************************************************/ 

class json
{
public:

    enum FLAGS {

        COMPACT = (1<<0),

    };

	//! Serialization

	static std::string& serialize(std::string& destination, const std::string& name, const any& value, word32 flags=0);

	template <class T>
	static std::string& serialize(std::string& destination, const std::string& name, const T* value, word32 flags=0)
	{
		any a = value;
		return laurena::json::json::serialize(destination,name,a,flags);
	}

	template<class T>
	static std::string serialize(const T* value, word32 flags =0)
	{
		any a = value;
		std::string destination;
		laurena::json::json::serialize(destination,a.desc()->name(),a,flags);
		return destination;
	}

	template<class T>
	static std::string serialize(const T& value, word32 flags =0)
	{
		any a = &value;
		std::string destination;
		laurena::json::json::serialize(destination,a.desc()->name(),a,flags);
		return destination;
	}

	//! Parsing
	

	template <class T>
	static T& parse(const std::string& json, const std::string& expected_name, T& destination)
	{
		any a = &destination;
		laurena::json::json::parse<any>(json,expected_name,a);
		return destination;
	}

	template <class T>
	static T& parse(const std::string& json, T& destination)
	{
		any a = &destination;
		laurena::json::json::parse<any>(json,a.desc()->name(),a);
		return destination;
	}

	template <>
	static any& parse<any>(const std::string& json, const std::string& expected_name, any& value)
	{
		iarchive_json amdl ;
		amdl.reader().str(json.c_str());

		try 
		{
			return amdl.parse(expected_name,value) ;
		}
		catch (const exception& e)
		{        
			std::ostringstream message ;
			(amdl.reader().prefixErrorMessage(message)) << e.message ();
			throw LAURENA_FAILED_PARSING_EXCEPTION( message.str().c_str(),amdl.reader()._ptr) ;      
		}   
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file