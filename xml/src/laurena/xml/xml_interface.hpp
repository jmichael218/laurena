///
/// \file     xml_interface.hpp
/// \brief    interface to mask internal calls to serialize from/to xml
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to xml
///
#ifndef LAURENA_INTERFACE_XML_H
#define LAURENA_INTERFACE_XML_H

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
#include <laurena/xml/xml_iarchive.hpp>
#include <laurena/toolboxes/loader.hpp>

#include <boost/filesystem.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace xml {

/***********************************************************************************/ 
/* json interface                                                                  */ 
/***********************************************************************************/ 
namespace xml_impl
{
	template <typename T>
	inline T& parse(const std::string& source, const std::string& expected_name, T& destination)
	{
		any a = &destination;
		laurena::xml::xml_impl::parse(source,expected_name,a);
		return destination;
	}

	template <>
	inline any& parse<any>(const std::string& source, const std::string& expected_name, any& value)
	{
		iarchive_xml axml ;
		axml.reader().str(source.c_str());

		try 
		{
			return axml.parse(expected_name,value) ;
		}
		catch (const exception& e)
		{        
			std::ostringstream message ;
			(axml.reader().prefixErrorMessage(message)) << e.message ();
			throw LAURENA_FAILED_PARSING_EXCEPTION( message.str().c_str(),axml.reader()._ptr) ;      
		}   
	}

    template<typename T>
    inline T& parseFile(const std::string& filename, const std::string& expected_name, T& destination)
	{
		any a = &destination;
		laurena::xml::xml_impl::parseFile(filename,expected_name,a);
		return destination;
	}

	template <>
	inline any& parseFile<any>(const std::string& filename, const std::string& expected_name, any& value)
	{
		iarchive_xml axml ;

		try 
		{
		    return axml.load(filename, expected_name, value);
		}
		catch (const exception& e)
		{        
			std::ostringstream message ;
			(axml.reader().prefixErrorMessage(message)) << e.message ();
			throw LAURENA_FAILED_PARSING_EXCEPTION( message.str().c_str(),axml.reader()._ptr) ;      
		}   
	}

}

class xml
{
public:


	//! Serialization

	static std::string& serialize(std::string& destination, const std::string& name, const any& value);

	template <class T>
	static std::string& serialize(std::string& destination, const std::string& name, const T* value)
	{
		any a = value;
		return laurena::xml::xml::serialize(destination,name,a);
	}

	template<class T>
	static std::string serialize(const T* value)
	{
		any a = value;
		std::string destination;
		laurena::xml::xml::serialize(destination,a.desc()->name(),a);
		return destination;
	}

	template<class T>
	static std::string serialize(const T& value)
	{
		any a = &value;
		std::string destination;
		laurena::xml::xml::serialize(destination,a.desc()->name(),a);
		return destination;
	}

	//! Parsing
	

	template <class T>
	static T& parse(const std::string& src, const std::string& expected_name, T& destination)
	{
		return xml_impl::parse(src, expected_name, destination);
	}

	template <class T>
	static T& parse(const std::string& src, T& destination)
	{
		any a = &destination;
		return xml_impl::parse(src, a.desc()->name(), destination);
	}

    template<class T>
    static T& parseFile(const std::string& filename, const std::string& expected_name, T& destination)
    {
        return xml_impl::parseFile(filename, expected_name, destination);
    }
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file