///
/// \file     loader.hpp
/// \brief    A toolbox of functions to load file contents
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions to load file contents
///

#ifndef LAURENA_LOADER_H
#define LAURENA_LOADER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 

#include <string>
#include <fstream>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              chartype dependant loader                                       */ 
/********************************************************************************/ 
template<typename CHARTYPE=char, typename DESTINATION=std::string, typename FILENAME=std::string>
class loader {
public:

	static DESTINATION  load(const FILENAME& filename)
	{
		DESTINATION s;
		return loader<CHARTYPE, DESTINATION, FILENAME>::load(filename, s);
	}

	static DESTINATION& load(const FILENAME& filename, DESTINATION& destination)
	{
		std::basic_ifstream<CHARTYPE> t(filename);

		t.seekg(0, std::ios::end);   
		destination.reserve((unsigned long int)t.tellg());
		t.seekg(0, std::ios::beg);

		destination.assign((std::istreambuf_iterator<CHARTYPE>(t)),
			std::istreambuf_iterator<CHARTYPE>());

		return destination;
	}

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
