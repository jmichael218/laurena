///
/// \file     mdl_interface.hpp
/// \brief    interface to mask internal calls to serialize from/to mdl
/// \author   Frederic Manisse
/// \version  1.0
///
/// interface to mask internal calls to serialize from/to mdl
///
#ifndef LAURENA_INTERFACE_MDL_H
#define LAURENA_INTERFACE_MDL_H

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
#include <laurena/mdl/iarchive_mdl.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {
namespace mdl {

/***********************************************************************************/ 
/* json interface                                                                  */ 
/***********************************************************************************/ 
namespace mdl_impl
{
	template <typename T>
	inline T& parse(const std::string& source, const std::string& expected_name, T& destination)
	{
		any a = &destination;
		laurena::mdl::mdl_impl::parse(source,expected_name,a);
		return destination;
	}

	template <>
	inline any& parse<any>(const std::string& source, const std::string& expected_name, any& value)
	{
		iarchive_mdl amdl ;
		amdl.reader().str(source.c_str());

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

}

class mdl
{
public:


	//! Serialization

	static std::string& serialize(std::string& destination, const std::string& name, const any& value);

	template <class T>
	static std::string& serialize(std::string& destination, const std::string& name, const T* value)
	{
		any a = value;
		return laurena::mdl::mdl::serialize(destination,name,a);
	}

	template<class T>
	static std::string serialize(const T* value)
	{
		any a = value;
		std::string destination;
		laurena::mdl::mdl::serialize(destination,a.desc()->name(),a);
		return destination;
	}

	template<class T>
	static std::string serialize(const T& value)
	{
		any a = &value;
		std::string destination;
		laurena::mdl::mdl::serialize(destination,a.desc()->name(),a);
		return destination;
	}

	//! Parsing
	

	template <class T>
	static T& parse(const std::string& src, const std::string& expected_name, T& destination)
	{
		return mdl_impl::parse(src, expected_name, destination);
	}

	template <class T>
	static T& parse(const std::string& src, T& destination)
	{
		any a = &destination;
		return mdl_impl::parse(src, a.desc()->name(), destination);
	}

	/*
	template <>
	static any& parse<any>(const std::string& mdl, const std::string& expected_name, any& value)
	{
		iarchive_mdl amdl ;
		amdl.reader().str(mdl.c_str());

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

	*/
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}}
#endif
//end of file