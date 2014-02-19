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
#include <laurena/archives/iarchive.hpp>
#include <laurena/archives/oarchive.hpp>

using namespace laurena;

/********************************************************************************/ 
/*      coplien compliant constructors                                          */ 
/********************************************************************************/ 
language::language () : 
      _name()
    , _tokens_parsers()
    , _tabs_parsers()
    , _format_annotations()
    , _reader_constructor()
    , _writer_constructor()
{ 
    this->set_default_format_annotations();
}

language::language (const std::string &name, const class parsers &ref_tokens_parsers,  const class parsers &ref_tabs_parsers) :

          _name (name)
        , _tokens_parsers(ref_tokens_parsers)
        , _tabs_parsers(ref_tabs_parsers)
        , _format_annotations()
        , _reader_constructor()
        , _writer_constructor()

{ 
    this->set_default_format_annotations();
}

language::language (const language &source) : 

      _name(source._name)
    , _tokens_parsers(source._tokens_parsers)
    , _tabs_parsers(source._tabs_parsers)
    , _format_annotations(source._format_annotations)
    , _reader_constructor(source._reader_constructor)
    , _writer_constructor(source._writer_constructor)

{ }

language::language (      language &&source) :
      _name(source._name)
    , _tokens_parsers(source._tokens_parsers)
    , _tabs_parsers(source._tabs_parsers)
    , _format_annotations(source._format_annotations)
    , _reader_constructor(source._reader_constructor)
    , _writer_constructor(source._writer_constructor)

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

void language::reader_constructor(std::function<std::shared_ptr<iarchive> ()> constructor)
{
    this->_reader_constructor = constructor;
}

void language::writer_constructor(std::function<std::shared_ptr<oarchive> ()> constructor)
{
    this->_writer_constructor = constructor;
}

/********************************************************************************/ 
/*          creating classes related to language used                           */ 
/********************************************************************************/ 
std::shared_ptr<iarchive> language::reader()
{
    return (this->_reader_constructor == nullptr) ? nullptr : this->_reader_constructor();    
}

std::shared_ptr<oarchive> language::writer() 
{
    return (this->_writer_constructor == nullptr) ? nullptr : this->_writer_constructor();  
}
//End of file