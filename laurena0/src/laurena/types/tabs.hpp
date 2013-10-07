///
/// \file     tabs.hpp
/// \brief    This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// This class allows to handle tabs display ( space or tab character ) , tab size increase and decrease.
///

#ifndef LAURENA_TABS_H
#define LAURENA_TABS_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <ostream>
#include <string>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          tab handler class					                                 */ 
/*********************************************************************************/ 
template<typename CHARTYPE=char>
class tabs
{
	public:    
	/****************************************************************************/
	/*      typedef                                                             */ 
	/****************************************************************************/ 
	typedef std::basic_string<CHARTYPE>				string;

	/****************************************************************************/
	/*      constructors                                                        */ 
	/****************************************************************************/ 
	tabs (const string& sequence = "\t", unsigned short int initial_length = 0) : 
		
		_sequence (sequence) , 
		_tab_length(initial_length)
	
		{
			for (unsigned short int i = 0; i < initial_length; i ++) 
				_tab.append(sequence);
		}

	tabs (const CHARTYPE* sequence, unsigned short int initial_length = 0) : 

		_sequence (sequence) , 
		_tab_length(initial_length)

	{
		for (unsigned short int i = 0; i < initial_length; i ++) 
			_tab.append(sequence);
	}


	/****************************************************************************/ 
	/*      operations                                                          */ 
	/****************************************************************************/ 
	tabs& decrease ()
	{
		if (this->_tab_length)					 
			this->_tab.erase (-- this->_tab_length * this->_sequence.length());
		
		return *this;
	}

	

	tabs& increase ()
	{
		++ this->_tab_length;
		this->_tab.append(this->_sequence);
		return *this;
	}


	inline 
	tabs& operator++ ()
	{ return this->increase(); }		

	inline 
	tabs& operator-- ()
	{ return this->decrease(); }

	inline const string& str() const    
	{ return this->_tab ; }


	/****************************************************************************/ 
	/*      protected member data                                               */ 
	/****************************************************************************/ 
	protected:

	string				_sequence ;       // tab sequence. Can be '\t' or '    ' or whatever
	string				_tab;			  // the current tab string. ( equal _table_length * _sequence )
	unsigned short int  _tab_length;      // how many tab characters must be inserted   


};

/********************************************************************************/ 
/*          other functions                                                     */ 
/********************************************************************************/ 
template<typename CHARTYPE>
inline std::basic_ostream<CHARTYPE>& operator << (std::basic_ostream<CHARTYPE>& dest, const tabs<CHARTYPE>& t)
{
	return dest << t.str();
}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
