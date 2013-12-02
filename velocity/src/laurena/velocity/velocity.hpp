///
/// \file     velocity.hpp
/// \brief    Main file to include to use the Velocity language as script language for output.
/// \author   Frederic Manisse
/// \version  1.0
///
/// \brief    Main file to include to use the Velocity language as script language for output.
///
#ifndef LAURENA_VELOCITY_H
#define LAURENA_VELOCITY_H

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

class velocity
{
public:

	std::string render(const std::string& source);

	inline class context& context() { return this->_context; }

	/****************************************************************************/ 
	/*				protected functions											*/ 
	/****************************************************************************/ 
	protected:

	const char* handleSharpCharacter(const char* src, std::ostream& output);
	const char* handleDollarCharacter(const char* src, std::ostream& output);

	const char* skipComment(const char* src);
	const char* skipSingleLineComment(const char* src);

	/****************************************************************************/ 
	/*				protected datas												*/ 
	/****************************************************************************/ 
	protected:

	class context					_context;

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file