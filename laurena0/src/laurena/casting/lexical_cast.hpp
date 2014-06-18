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

#include <laurena/traits/toolbox/toolbox.hpp>

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

template<typename SOURCE>
struct lexical_cast_impl<std::string, SOURCE>
{
	inline static std::string cast(SOURCE s)
	{ return toolbox<SOURCE>::tos(s); }
};


/*********************************************************************************/ 
/*				from string														 */ 
/*********************************************************************************/ 
template<typename SOURCE>
struct lexical_cast_impl<SOURCE, std::string>
{
	inline static SOURCE cast(const std::string& s)
	{ return toolbox<SOURCE>::froms(s); }
};


/*********************************************************************************/ 
/*				from const char*    											 */ 
/*********************************************************************************/ 
template<typename SOURCE>
struct lexical_cast_impl<SOURCE, const char*>
{
    inline static SOURCE cast(const char* source)
    { return toolbox<SOURCE>::fromcc(source); }
};

/*
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
*/
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