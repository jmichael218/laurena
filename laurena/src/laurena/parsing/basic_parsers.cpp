///
/// \file     parser.cpp
/// \brief    parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
///
#include <laurena/parsing/basic_parsers.hpp>
#include <laurena/parsing/tokenizer.hpp>
#include <laurena/toolboxes/stdstring.hpp>
#include <laurena/toolboxes/cstring.hpp>
#include <laurena/constants/const_charsets.hpp>
#include <laurena/memory/memory_functions.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class single_character_parser                              */ 
/*                                                                              */ 
/********************************************************************************/ 

//constructor
single_character_parser::single_character_parser (word8 character) : parser () , _character (character)
{ }

// destructor
single_character_parser::~single_character_parser()
{ }

//parser function
bool single_character_parser::read (tokenizer& tokenizer, any& value, bool consume) const 
{
    
    bool res = (*tokenizer._ptr == this->_character);
    if (res)
    {                
        value = std::string((const char*)&this->_character,1);
        if (consume)
        {
            tokenizer._location.process (*tokenizer._ptr);
            tokenizer._ptr ++;
        }
    }
    return res;
}

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class keyword_parser                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

// tokenizer function : read fixed keyword insensitive
keyword_parser::keyword_parser(const char* keyword) : parser () , _keyword(keyword)
{ }

keyword_parser::~keyword_parser()
{ }

bool keyword_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{

    bool res = cstring::startWith(tokenizer._ptr,this->_keyword.c_str(),false,this->_keyword.length());

    if(res)
    {
        value = this->_keyword;
        if (consume)
        {
            tokenizer._location.process (this->_keyword);
            tokenizer._ptr += this->_keyword.length();
        }        
    }
    return res;
    
}

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class keyword_parser                                       */ 
/*                                                                              */ 
/********************************************************************************/ 

signed_integer_parser::signed_integer_parser () : parser()
{}

signed_integer_parser::~signed_integer_parser()
{}

bool signed_integer_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{ 
    std::string v ;
    word32 readed = cstring::readInteger(tokenizer._ptr,v);

    if (!readed)
        return false;

    value = v;

    if (consume)
    {
        tokenizer._location.process (v);
        tokenizer._ptr += readed;
    }

    return true;       

}

/********************************************************************************/ 
/*                                                                              */ 
/*          code for class hexadecimal_parser                                   */ 
/*                                                                              */ 
/********************************************************************************/ 

hexadecimal_parser::hexadecimal_parser () : parser()
{}

hexadecimal_parser::~hexadecimal_parser()
{}

bool hexadecimal_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
const char* p = tokenizer._ptr;

    if (*(p++) != '0' )
        return false;

    if (*p != 'x' && *p != 'X')
        return false;

    p ++;
    std::string v = cstring::readWhile(p,CHARSET_HEXANUMBER);

    v.insert(0,tokenizer._ptr,2);
    value = v;
    if (consume)
    {
        tokenizer._location.process(v);
        tokenizer._ptr += v.length();
    }
    return true;  
    
}

/********************************************************************************/ 
/*                                                                              */ 
/*          single string reader ( quoted with " " )                            */ 
/*                                                                              */ 
/********************************************************************************/ 
string_parser::string_parser () : parser ()
{ }

string_parser::~string_parser ()
{ }

bool string_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
    if (*tokenizer._ptr != '"')
        return false;
    const char* p = tokenizer._ptr+1;    

    word32 idx=0;

    while ( (*p) && (*p  != '"' )  )
    {
        ++p ; 
        ++idx;
    }

    if (!*p)
        return false;

    value = std::string(tokenizer._ptr+1,idx);

    if (consume)
    {
        tokenizer._location.process(tokenizer._ptr,idx+2);
        tokenizer._ptr += idx +2;
        
    }

    return true;
}

/********************************************************************************/ 
/*                                                                              */ 
/*          multiline string reader ( quoted with " " )                         */ 
/*                                                                              */ 
/********************************************************************************/ 

multi_string_parser::multi_string_parser () : parser ()
{ }

multi_string_parser::~multi_string_parser()
{}

bool multi_string_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{    
const char* p = tokenizer._ptr;
word32 idx=0;
std::ostringstream buf ;
bool end = false;
std::string b ;

    while (true)
    {
        p = cstring::skipWhile(p,CHARSET_TABS);
        if ( *p != '"' )
            break;

        p++;

        b = cstring::readUntil(p,'"');
        p += b.length ();

        if ( *p != '"' )
            return false ;

        if ( b.length() == 0)
            buf << std::endl;
        else
            buf << b;
                
        p ++;
    }

    b = buf.str();
    if ( b.length() == 0)
        return false;
    
    if (consume)
    {
        word32 sz = memory::offset(tokenizer._ptr,p);
        tokenizer._location.process (tokenizer._ptr,sz);
        tokenizer._ptr += sz;
    }

   value = b ;
    return true;
}

/********************************************************************************/ 
/*                                                                              */ 
/*          read EOL                                                            */ 
/*                                                                              */ 
/********************************************************************************/ 
eol_parser::eol_parser () : parser ()
{ }

eol_parser::~eol_parser()
{}

bool eol_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
    if (*tokenizer._ptr != '\n')
        return false;

    value = std::string('\n',1);

    if (consume)
    {
        tokenizer._location.process('\n');
        tokenizer._ptr ++;
    }
    return true;

}

/********************************************************************************/ 
/*                                                                              */ 
/*          read Tabs                                                           */ 
/*                                                                              */ 
/********************************************************************************/ 
tabs_parser::tabs_parser () : parser ()
{ }

tabs_parser::~tabs_parser ()
{}

bool tabs_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{

    std::string keyword = cstring::readWhile(tokenizer._ptr,CHARSET_TABS2);
    if (!keyword.length())
        return false;

    value = keyword;
    if (consume)
    {
        tokenizer._location.process (keyword);
        tokenizer._ptr += keyword.length();
    }
    return true;  
}


/********************************************************************************/ 
/*                                                                              */ 
/*          accept any length belonging to a charset                            */ 
/*                                                                              */ 
/********************************************************************************/
charset_parser::charset_parser(const charset& cset, bool until) : parser (), _charset(cset), _until(until)
{ }

charset_parser::~charset_parser()
{}

bool charset_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
    
    std::string keyword = this->_until ? cstring::readUntil(tokenizer._ptr,this->_charset) : cstring::readWhile(tokenizer._ptr,this->_charset);
    if (!keyword.length())
        return false;

    value = keyword;
    if (consume)
    {
        tokenizer._location.process ( keyword);
        tokenizer._ptr += keyword.length();
    }
    return true;   
}

/********************************************************************************/ 
/*                                                                              */ 
/*              accept any character but a given length                         */ 
/*                                                                              */ 
/********************************************************************************/ 
length_parser::length_parser (word32 length) : parser (), _length(length)
{ }

length_parser::~length_parser ()
{ }


bool length_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{

    word32 still = tokenizer._source.length();
    if ( still < this->_length )
        return false;

    value = std::string(tokenizer._ptr,this->_length);
    if (consume)
    {
        tokenizer._location.process (*tokenizer._ptr);
        tokenizer._ptr ++;
    }    
    return true;
}

//end of file
