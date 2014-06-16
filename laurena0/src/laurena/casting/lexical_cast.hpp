///
/// \file     lexical_cast.hpp
/// \brief    a home made lexical_cast<type_destination, type_source>(source) template function to avoid dependancie to boost
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  a home made lexical_cast<type_destination, type_source>(source) template function to avoid dependancie to boost
///

#ifndef LAURENA_LEXICAL_CAST_H
#define LAURENA_LEXICAL_CAST_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              include section                                                 */ 
/********************************************************************************/ 
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <limits>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/*********************************************************************************/
/*         voidptr caster                                                        */ 
/*********************************************************************************/ 

template<typename TARGET, typename SOURCE>
struct lexical_cast_impl
{
	// no function to prevent compilation if the right lexical_cast is not implemented
	/*
	static TARGET cast (SOURCE source)
	{
		std::string message;
		message = "No conversion implemented in laurena::lexical_cast from ";
		message.append(typeid(SOURCE).name());
		message.append(" to ");
		message.append(typeid(TARGET).name());
		throw std::runtime_error(message);
	}
	*/
};

/*********************************************************************************/ 
/*				to string 														 */
/*********************************************************************************/ 
template<typename SOURCE>
struct lexical_cast_to_string
{ 
	inline static std::string cast(SOURCE source)
	{ return std::to_string(source); }
};

template<>
struct lexical_cast_impl<std::string, signed char>
{
	inline static std::string cast(signed char c)
	{ return std::to_string((int) c); }
};

template<>
struct lexical_cast_impl<std::string, unsigned char>
{
	inline static std::string cast(unsigned char c)
	{ return std::to_string((int) c); }
};

template<>
struct lexical_cast_impl<std::string, unsigned int> : public lexical_cast_to_string<unsigned int> {};

template<>
struct lexical_cast_impl<std::string, int> : public lexical_cast_to_string<int> {};

template<>
struct lexical_cast_impl<std::string, unsigned short int> : public lexical_cast_to_string<unsigned short int> {};

template<>
struct lexical_cast_impl<std::string, short int> : public lexical_cast_to_string<short int> {};

template<>
struct lexical_cast_impl<std::string, unsigned long int> : public lexical_cast_to_string<unsigned long int> {};

template<>
struct lexical_cast_impl<std::string, long int> : public lexical_cast_to_string<long int> {};

template<>
struct lexical_cast_impl<std::string, unsigned long long int> : public lexical_cast_to_string<unsigned long long int> {};

template<>
struct lexical_cast_impl<std::string, long long int> : public lexical_cast_to_string<long long int> {};

template<>
struct lexical_cast_impl<std::string, float> : public lexical_cast_to_string<float> {};

template<>
struct lexical_cast_impl<std::string, double> : public lexical_cast_to_string<double> {};

template<>
struct lexical_cast_impl<std::string, long double> : public lexical_cast_to_string<long double> {};

/*********************************************************************************/ 
/*				from string														 */ 
/*********************************************************************************/ 
template<>
struct lexical_cast_impl<signed char, std::string>
{
	static signed char cast(const std::string& source)	
	{ 
		int i = std::stoi(source); 
		if (
			(i < (int) std::numeric_limits<char>::min()) ||
			(i > (int) std::numeric_limits<char>::max())
		   )
		throw std::out_of_range("Outside char range");
		return (char) i;
	}
};

template<>
struct lexical_cast_impl<unsigned char, std::string>
{
	static unsigned char cast(const std::string& source)	
	{ 
		unsigned long int i = std::stoul(source); 
		if (
			(i > (unsigned long int) std::numeric_limits<unsigned char>::max())
		   )
		throw std::out_of_range("Outside unsigned char range");
		return (unsigned char) i;
	}
};

template<>
struct lexical_cast_impl<short int, std::string>
{
	static short int cast(const std::string& source)	
	{ 
		int i = std::stoi(source); 
		if (
			(i < (int) std::numeric_limits<short int>::min()) ||
			(i > (int) std::numeric_limits<short int>::max())
		   )
		throw std::out_of_range("Outside short int range");
		return (short int) i;
	}
};

template<>
struct lexical_cast_impl<unsigned short int, std::string>
{
	static unsigned short int cast(const std::string& source)	
	{ 
		unsigned long int i = std::stoul(source); 
		if (
			(i > (unsigned long int) std::numeric_limits<unsigned short int>::max())
		   )
		throw std::out_of_range("Outside unsigned short int range");
		return (unsigned short int) i;
	}
};

template<>
struct lexical_cast_impl<unsigned int, std::string>
{
	inline static unsigned int cast(const std::string& source)
	{ return (unsigned int) std::stoul(source); }	
};

template<>
struct lexical_cast_impl<int, std::string>
{
	inline static int cast(const std::string& source)
	{ return std::stoi (source); }	
};

template<>
struct lexical_cast_impl<long int, std::string>
{
	inline static long int cast(const std::string& source)
	{ return std::stol(source); }
};

template<>
struct lexical_cast_impl<unsigned long int, std::string>
{
	inline static unsigned long int cast(const std::string& source)
	{ return std::stoul(source); }
};

template<>
struct lexical_cast_impl<long long int, std::string>
{
	inline static long long int cast(const std::string& source)
	{ return std::stoll(source); }
};

template<>
struct lexical_cast_impl<unsigned long long int, std::string>
{
	inline static unsigned long long int cast(const std::string& source)
	{ return std::stoull(source); }
};


/*********************************************************************************/ 
/*				from const char*    											 */ 
/*********************************************************************************/ 

template<>
struct lexical_cast_impl<unsigned int, const char*>
{
	inline static unsigned int cast(const char* source)
	{ return (unsigned int) std::stoul(std::string(source)); }
};

template<>
struct lexical_cast_impl<int, const char*>
{
	inline static int cast(const char* source)
	{ return atoi(source); }
};

template<>
struct lexical_cast_impl<unsigned short int, const char*>
{
	inline static unsigned short int cast(const char* source)
	{ return (unsigned short int) atoi(source); }
};

/*********************************************************************************/ 
/*				lexical_cast function 											 */ 
/*********************************************************************************/ 
template<typename TARGET, typename SOURCE>
inline
TARGET lexical_cast(const SOURCE& source)
{
	return lexical_cast_impl<TARGET, SOURCE>::cast(source);
}




/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif