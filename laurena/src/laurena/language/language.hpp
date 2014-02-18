///
/// \file     language.hpp
/// \brief    Base class for commun features of all language used to serialize objects
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for commun features of all language used to serialize objects
///
#ifndef LAURENA_LANGUAGE_H
#define LAURENA_LANGUAGE_H

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

#include <laurena/parsing/parser.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              forward declaration                                             */ 
/********************************************************************************/ 
class iarchive;
class oarchive;

/********************************************************************************/ 
/*              class language                                                  */ 
/********************************************************************************/ 

class language
{
public:

    /****************************************************************************/
    /*          constructors, destructor                                        */ 
    /****************************************************************************/ 
    language ();
    language (const std::string &name, const class parsers &ref_tokens_parsers,  const class parsers &ref_tabs_parsers);
    language (const language &source);
    language (      language &&source);

    virtual ~language ();

    /****************************************************************************/ 
    /*          operators                                                       */ 
    /****************************************************************************/ 
    language& operator=(const language &source);
    language& operator=(      language &&source);

    /****************************************************************************/ 
    /*          building the language                                           */ 
    /****************************************************************************/ 

    /*
     * \brief set default names for format annotations
     *
     * Set to the language the default format annotations names. 
     * These names are 0 : "format." + _name
     *                 1 : "format.all"
     */
    void set_default_format_annotations();

    /****************************************************************************/ 
    /*          accessors                                                       */ 
    /****************************************************************************/ 

    /*
     * \brief return language name like "json" or "xml"
     *
     * This function return the language name. Expected values are "json", "xml", etc ...
     *
     * \return The language name
     */
    const std::string& name() const;

    language& name(const std::string   &value);
    language& name(      std::string  &&rvalue);

    const class parsers& tokens_parsers() const;
    language& tokens_parsers(const class parsers  &value);
    language& tokens_parsers(      class parsers &&rvalue);

    const class parsers tabs_parsers() const;

    language& tabs_parsers(const class parsers  &value);
    language& tabs_parsers(      class parsers &&rvalue);


    const std::vector<std::string>& format_annotations() const;

    std::shared_ptr<iarchive>       reader();
    std::shared_ptr<oarchive>       writer();

    /****************************************************************************/
    /*          member datas                                                    */ 
    /****************************************************************************/ 
    protected:

    std::string                 _name;
    class parsers               _tokens_parsers;
    class parsers               _tabs_parsers;

    std::vector<std::string>    _format_annotations;

    std::function<std::shared_ptr<iarchive> ()>        _reader_constructor;
    std::function<std::shared_ptr<oarchive> ()>        _writer_constructor;


};

/********************************************************************************/ 
/*          inline functions                                                    */ 
/********************************************************************************/ 

/********************** accessors on field _name ********************************/ 
inline 
const std::string& language::name() const
{ return this->_name; }

inline
language& language::name(const std::string& value)
{ this->_name = value; return *this; }

inline
language& language::name(      std::string&& value)
{ this->_name = value; return *this; }

/********************** accessors on field _tokens_parsers ************************/ 
inline
const class parsers& language::tokens_parsers() const
{ return this->_tokens_parsers; }

inline
language& language::tokens_parsers(const class parsers  &value)
{ this->_tokens_parsers = value; return *this; }

inline
language& language::tokens_parsers(      class parsers &&rvalue)
{ this->_tokens_parsers = rvalue; return *this; }


/********************** accessors on field _tabs_parsers **************************/ 
inline
const class parsers language::tabs_parsers() const
{ return this->_tabs_parsers; }

inline
language& language::tabs_parsers (const class parsers&  value)
{ this->_tabs_parsers = value; return *this; }

inline
language& language::tabs_parsers (      class parsers&& rvalue)
{ this->_tabs_parsers = rvalue; return *this; }

/*********************** accessors on format_annotations ************************/ 
inline    
const std::vector<std::string>& language::format_annotations() const
{  return this->_format_annotations; }

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file