///
/// \file     language.cpp
/// \brief    Base class for commun features of all language used to serialize objects
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for commun features of all language used to serialize objects
///
#include <laurena/language/language.hpp>
#include <laurena/constants/const_strings.hpp>

using namespace laurena;

/********************************************************************************/ 
/*      coplien compliant constructors                                          */ 
/********************************************************************************/ 
language::language () : 
      _name()
    , _tokens_parsers()
    , _tabs_parsers()
    , _format_annotations()
{ 
    this->set_default_format_annotations();
}

language::language (const std::string &name, const class parsers &ref_tokens_parsers,  const class parsers &ref_tabs_parsers) :

          _name (name)
        , _tokens_parsers(ref_tokens_parsers)
        , _tabs_parsers(ref_tabs_parsers)
        , _format_annotations()

{ 
    this->set_default_format_annotations();
}

language::language (const language &source) : 

      _name(source._name)
    , _tokens_parsers(source._tokens_parsers)
    , _tabs_parsers(source._tabs_parsers)
    , _format_annotations(source._format_annotations)

{ }

language::language (      language &&source) :
      _name(source._name)
    , _tokens_parsers(source._tokens_parsers)
    , _tabs_parsers(source._tabs_parsers)
    , _format_annotations(source._format_annotations)

{ }

/********************************************************************************/ 
/*      destructor                                                              */ 
/********************************************************************************/ 

 language::~language ()
 { }

/********************************************************************************/ 
/*          coplien compliant operators                                         */ 
/********************************************************************************/ 
language& language::operator=(const language &source)
{
    this->_name                 = source._name;
    this->_tokens_parsers       = source._tokens_parsers;
    this->_tabs_parsers         = source._tabs_parsers;
    this->_format_annotations   = source._format_annotations;
    return *this;
}


language& language::operator=(      language &&source)
{
    this->_name                 = source._name;
    this->_tokens_parsers       = source._tokens_parsers;
    this->_tabs_parsers         = source._tabs_parsers;
    this->_format_annotations   = source._format_annotations;
    return *this;
}

/********************************************************************************/ 
/*          building the language                                               */ 
/********************************************************************************/ 
void language::set_default_format_annotations()
{
    this->_format_annotations.resize(2);
    this->_format_annotations[1] = ANNOTATION_FORMAT_ALL;
    (this->_format_annotations[0] = "format.").append(this->_name);
    
}
//End of file