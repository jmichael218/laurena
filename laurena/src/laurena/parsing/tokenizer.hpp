///
/// \file     tokenizer.hpp
/// \brief    A tokenizer class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A tokenizer class
///

#ifndef LAURENA_TOKENIZER_H
#define LAURENA_TOKENIZER_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/types/source_location.hpp>

#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/parsing/token.hpp>
#include <laurena/parsing/parser.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*                                                                              */ 
/*              class tokenizer                                                 */ 
/*                                                                              */ 
/********************************************************************************/ 
class tokenizer 
{
public:

    class state 
    {
        public:
        state (const std::string& source, const char* ptr)  : _source (source.c_str()) , _ptr (ptr) {}
        state& operator= (const state& s) { _source = s._source; _ptr = s._ptr ; }

        protected:
        const char*         _source;
        const char*         _ptr;

        friend class tokenizer ;
    };


    /****************************************************************************/ 
    /*          constructors, destructor                                        */ 
    /****************************************************************************/ 
    tokenizer();
    virtual ~tokenizer();

    /****************************************************************************/ 
    /*          source loading / setters                                        */ 
    /****************************************************************************/ 
    void load(const std::string& filename);
    void str(const char* source);

    /****************************************************************************/ 
    /*          tokenize                                                        */ 
    /****************************************************************************/   
    void skip(const parsers& ps);
    int32 read(any& value, const parsers& ps);
    int32 read(any& value, const parsers& ps, const boost::dynamic_bitset<>& allowed);

    int32 readExpected(any& value, const parsers& ps, const boost::dynamic_bitset<>& tabs, word8 expected);

    std::ostream& prefixErrorMessage(std::ostream& message) const;
    void syntaxError (const std::string& message) const;

    void skipCurrentLine ();
    void skipUntil (const char* keyword, bool skipKeyword = false);
    std::string readUntil (const char* keyword, bool skipKeyword);

    /****************************************************************************/
    /*          straight tokenizing                                             */ 
    /****************************************************************************/ 
    tokenizer& operator >> (const char c);
    tokenizer& operator >> (int32& i);
    tokenizer& operator >> (word32& w);
    tokenizer& operator>>  (int16& i);
    tokenizer& operator>>  (word16& w);

    
    /*****************************************************************************/
    /*          get state and restore for consume & error handling               */
    /*****************************************************************************/ 
    inline state        current () const            { return state(_source,_ptr); }
           tokenizer&   restore (const state& s);

    /****************************************************************************/ 
    /*              protected:                                                  */ 
    /****************************************************************************/
    public:


    std::string             _source;
    const char*             _ptr;
    source_location<>       _location;
};

template<>
struct in_traits<tokenizer>
{
	typedef tokenizer								type;
	typedef char									chartype;
	typedef const char*								iterator;
	typedef std::string								string;

	inline
	static iterator first(const type& str)
	{ return str._ptr; }

	inline
	static iterator last(const type& str)
	{ return str._source.c_str() + str._source.length(); }

	inline
	static iterator readed(iterator it, unsigned long int length) 
	{ return it + length; }

	inline
	static iterator back(type& str, iterator current, chartype c)
	{ 
		--current;
		return current;
	}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif