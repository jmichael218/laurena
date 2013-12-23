///
/// \file     format.hpp
/// \brief    format is a parser + a writer pair
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// format is a parser + a writer pair
///

#ifndef LAURENA_FORMAT_H
#define LAURENA_FORMAT_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/classes.hpp>
#include <laurena/parsing/parser.hpp>
#include <laurena/parsing/tokenizer.hpp>
#include <laurena/formatting/writer.hpp>
#include <laurena/descriptors/annotation.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          base class for all parser classes                                    */ 
/*********************************************************************************/ 
class format : public annotation
{
public:    

    /****************************************************************************/ 
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
	format (const char* language);
    format (const char* language, std::shared_ptr<writer>& w, std::shared_ptr<parser> f);

    /****************************************************************************/ 
    /*          getters                                                         */ 
    /****************************************************************************/ 
    bool write (std::ostream& output, any& value) const;
    bool read (tokenizer& tokenizer, any& value, bool consume) const  ;     

	/****************************************************************************/ 
	/*			virtual functions from annotation								*/ 
	/****************************************************************************/ 
	virtual bool acceptDescriptable ();

    /****************************************************************************/ 
    /*      protected datas                                                     */ 
    /****************************************************************************/ 
    protected:

	// I use shared ptr because i don't know if writer and parser aren't used elsewhere, and when to free them
    std::shared_ptr<writer>     _writer;
    std::shared_ptr<parser>     _parser;
};

template<typename T>
class generic_format : public format
{
public:

	generic_format(const char* language) : format(language)
	{
		this->_writer = std::make_shared<generic_writer<T>>();
		this->_parser = std::make_shared<generic_parser<T>>();
	}

};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
