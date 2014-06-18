///
/// \file     toolbox_boost_dynamic_bitset.hpp
/// \brief    Specialisation of the toolbox template for boost::dynamic_bitset<>
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  Specialisation of the toolbox template for boost::dynamic_bitset<>

#ifndef LAURENA_TOOLBOX_BOOST_DYNAMIC_BITSET_H
#define LAURENA_TOOLBOX_BOOST_DYNAMIC_BITSET_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <laurena/traits/toolbox/toolbox.hpp>
#include <boost/dynamic_bitset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {


/********************************************************************************/ 
/*              toolbox<boost::dynamic_bitset<>>                                */ 
/********************************************************************************/ 

template<>
class toolbox_impl<boost::dynamic_bitset<>>
{
public:

    inline static std::string tos(const boost::dynamic_bitset<>& source)
	{ 
	    std::string destination (source.size(), '0');
	    auto it = destination.begin();

        for (boost::dynamic_bitset<>::size_type i = 0; i < source.size(); ++i, ++it)
            if (source.test(i))
                *it = '1' ;

        return destination;	    
	}
	
	inline static boost::dynamic_bitset<> froms(const std::string& source)
	{
	    boost::dynamic_bitset<> res(source.length());
	    auto it = source.begin();
	    
	   for (boost::dynamic_bitset<>::size_type i = 0; i < source.size(); ++i, ++it)
            res.test(*it != '0');
            
	    return res;
	
	}		
	
	inline static std::string mask_to_string
	(
	    const boost::dynamic_bitset<>& mask, 
	    const std::vector<std::string>& bitnames,
	    const std::string separator
	)
	{
	    std::string destination;
	    bool first (true);
	    auto itnames = bitnames.begin();
	    for (boost::dynamic_bitset<>::size_type i = 0; i < mask.size(); ++i, ++itnames)
	        if (mask.test(i))
	        {
	            if (first)
	                first = false;
	            else
	                destination.append(separator);
	            
	            destination.append(*itnames);
	        }
	    return destination;
	}
	
	inline static boost::dynamic_bitset<> string_to_mask
	(
	    const std::string& str,
	    const std::vector<std::string>& bitnames,
	    const std::string& separator
	)
	{
	    
	}
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
