///
/// \file     toolbox.hpp
/// \brief    Functions that must be specialized for each type, like tostring
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Functions that must be specialized for each type, like tostring

#ifndef LAURENA_TOOLBOX_H
#define LAURENA_TOOLBOX_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <type_traits>
#include <memory>
#include <string>
#include <vector>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/********************************************************************************/ 
/*              base class                                                      */ 
/********************************************************************************/ 

template<typename T>
class toolbox_impl
{ 
    /*
    
    // T to std::string
    inline static std::string tos(const T& source)
    { return std::to_string(source); }
        
    // std::string to T
    inline static T froms(const std::string& source)
    { 
        std::istringstream ss (source);
        T t;
        ss >> t;
        return t;
    }
        
    // const char* to T
    inline static T fromcc(const char* source)
    {
        std::istringstream ss (source);
        T t;
        ss >> t;
        return t;        
    }
        
     */
    
} ;

/********************************************************************************/ 
/*              int, unsigned int                                               */ 
/********************************************************************************/ 

template<>
class toolbox_impl<int>
{
public:

    inline static std::string tos(int source)
	{ return std::to_string(source); }    

	inline static int froms(const std::string& source)
	{ return std::stoi (source); }
	
	inline static int fromcc(const char* source)
	{ return atoi(source); }
};

template<>
class toolbox_impl<unsigned int>
{
public:

    inline static std::string tos(unsigned int source)
	{ return std::to_string(source); }
	
	inline static unsigned int froms(const std::string& source)
	{ return (unsigned int) std::stoul(source); }
	
	inline static unsigned int fromcc(const char* source)
	{ return (unsigned int) std::stoul(std::string(source)); }
};

/********************************************************************************/ 
/*              short int, short unsigned int                                   */ 
/********************************************************************************/ 
template<>
class toolbox_impl<short int>
{
public:

    inline static std::string tos(short int source)
	{ return std::to_string(source); }  
	
	static short int froms(const std::string& source)	
	{ 
		int i = std::stoi(source); 
		if (
			(i < (int) std::numeric_limits<short int>::min()) ||
			(i > (int) std::numeric_limits<short int>::max())
		   )
		throw std::out_of_range("Outside short int range");
		return (short int) i;
	}	
	
	inline static short int fromcc(const char* source)
	{ return toolbox_impl<short int>::froms(std::string(source)); }	
};

template<>
class toolbox_impl<unsigned short int>
{
public:

    inline static std::string tos(unsigned short int source)
	{ return std::to_string(source); }
	
	static unsigned short int froms(const std::string& source)	
	{ 
		unsigned long int i = std::stoul(source); 
		if (
			(i > (unsigned long int) std::numeric_limits<unsigned short int>::max())
		   )
		throw std::out_of_range("Outside unsigned short int range");
		return (unsigned short int) i;
	}	
	
	inline static unsigned short int fromcc(const char* source)
	{ return toolbox_impl<unsigned short int>::froms(std::string(source)); }		
};

/********************************************************************************/ 
/*              char, unsigned char                                             */ 
/********************************************************************************/ 
template<>
class toolbox_impl<signed char>
{
public:

	inline static std::string tos(signed char c)
	{ return std::to_string((int) c); }    
	
	static signed char froms(const std::string& source)	
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
class toolbox_impl<unsigned char>
{
public:

	inline static std::string tos(unsigned char c)
	{ return std::to_string((int) c); }
	
	inline static unsigned char froms(const std::string& source)
    {
		unsigned long int i = std::stoul(source); 
		if (
			(i > (unsigned long int) std::numeric_limits<unsigned char>::max())
		   )
		throw std::out_of_range("Outside unsigned char range");
		return (unsigned char) i;	
    }
};

/*********************************************************************************/ 
/*              long (unsigned) int                                              */ 
/*********************************************************************************/ 
template<>
class toolbox_impl<long int>
{
public:

    inline static std::string tos(long int source)
	{ return std::to_string(source); }   
	
	inline static long int froms(const std::string& source)
	{ return std::stol(source); }	
};

template<>
class toolbox_impl<long unsigned int>
{
public:

    inline static std::string tos(long unsigned int source)
	{ return std::to_string(source); }
	
	inline static unsigned long int froms(const std::string& source)
	{ return std::stoul(source); }	
};

/*********************************************************************************/ 
/*              long long (unsigned) int                                         */ 
/*********************************************************************************/ 
template<>
class toolbox_impl<long long int>
{
public:

    inline static std::string tos(long int source)
	{ return std::to_string(source); }
	
	inline static long long int froms(const std::string& source)
	{ return std::stoll(source); }	
};

template<>
class toolbox_impl<long long unsigned int>
{
public:

    inline static std::string tos(long unsigned int source)
	{ return std::to_string(source); }
	
	inline static unsigned long long int froms(const std::string& source)
	{ return std::stoull(source); }	
};

/*********************************************************************************/ 
/*              float, double                                                    */ 
/*********************************************************************************/ 

template<>
class toolbox_impl<float>
{
public:

    inline static std::string tos(float source)
	{ return std::to_string(source); }    
	
	inline static float froms(const std::string& source)
	{ return std::stof(source); }		
};

template<>
class toolbox_impl<double>
{
public:

    inline static std::string tos(double source)
	{ return std::to_string(source); }
	
	inline static double froms(const std::string& source)
	{ return std::stod(source); }		
};

/*********************************************************************************/ 
/*              toolbox classes                                                  */ 
/*********************************************************************************/
template<typename T>
class toolbox : public toolbox_impl<T> 
{ } ;


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
