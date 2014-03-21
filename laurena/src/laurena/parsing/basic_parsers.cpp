///
/// \file     parser.cpp
/// \brief    parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// parser classes are parsing units to parse a given format like integer, string, hexadecimal number , etc ...
///
#include <laurena/algorithm/strings/prefix.hpp>
#include <laurena/algorithm/strings/readwhile.hpp>
#include <laurena/algorithm/strings/readuntil.hpp>
#include <laurena/algorithm/strings/readinteger.hpp>
#include <laurena/algorithm/strings/skipwhile.hpp>

#include <laurena/parsing/basic_parsers.hpp>
#include <laurena/parsing/tokenizer.hpp>
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
            tokenizer._location.count (*tokenizer._ptr);
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
	bool res = prefix(tokenizer._ptr,this->_keyword.c_str());

    if(res)
    {
        value = this->_keyword;
        if (consume)
        {
            tokenizer._location.count (this->_keyword);
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
	std::string svalue = std::move(readinteger(tokenizer._ptr));
	word32 v = svalue.length();

    if (!v)
        return false;

    value = svalue;

    if (consume)
    {
        tokenizer._location.count (svalue);
        tokenizer._ptr += v;
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
    std::string v = readwhile(p,const_charsets<>::HEXADECIMAL.condition());

    v.insert(0,tokenizer._ptr,2);
    value = v;
    if (consume)
    {
        tokenizer._location.count(v);
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
        tokenizer._location.count(tokenizer._ptr,tokenizer._ptr+idx+2);
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
{
	_quote_condition = [] (const char& c) {return c == '"';};


}

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
        p = skipwhile(p,const_charsets<>::TABS.condition());
        if ( *p != '"' )
            break;

        p++;

        b = std::move(readuntil(p,_quote_condition));
        p += b.length ();

        if ( *p != '"' )
            return false ;

        if ( b.length() == 0)
            buf << "\r\n";
        else
            buf << b;
                
        p ++;
    }

    b = buf.str();
    if ( b.length() == 0)
        return false;
    
    if (consume)
    {
        tokenizer._location.count (tokenizer._ptr,p);
        tokenizer._ptr = p;
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
        tokenizer._location.count('\n');
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

    std::string keyword = readwhile(tokenizer._ptr,const_charsets<>::TABS_NO_EOL.condition());
    if (!keyword.length())
        return false;

    value = keyword;
    if (consume)
    {
        tokenizer._location.count (keyword);
        tokenizer._ptr += keyword.length();
    }
    return true;  
}


/********************************************************************************/ 
/*                                                                              */ 
/*          accept any length belonging to a charset                            */ 
/*                                                                              */ 
/********************************************************************************/
charset_parser::charset_parser(const charset<>& cset, bool until) : parser (), _charset(cset), _until(until)
{ }

charset_parser::~charset_parser()
{}

bool charset_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
    
    std::string keyword = this->_until ? readuntil(tokenizer._ptr,this->_charset.condition()) : readwhile(tokenizer._ptr,this->_charset.condition());
    if (!keyword.length())
        return false;

    value = keyword;
    if (consume)
    {
        tokenizer._location.count (keyword);
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
        tokenizer._location.count (*tokenizer._ptr);
        tokenizer._ptr ++;
    }    
    return true;
}

/********************************************************************************/ 
/*                                                                              */ 
/*              accept any length between a keyword and a given charset         */ 
/*  userfull for comment like // comment until end of line                      */ 
/*                                                                              */ 
/********************************************************************************/ 
keyword_to_charset_parser::keyword_to_charset_parser(const std::string& keyword, const charset<>& chars) : parser(), _keyword(keyword), _charset(chars)
{ }

keyword_to_charset_parser::~keyword_to_charset_parser()
{ }

bool keyword_to_charset_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
	if (! prefix(tokenizer._ptr,this->_keyword.c_str()))
        return false;

    const char* base = tokenizer._ptr + this->_keyword.length();
    std::string content = std::move( readuntil(base, this->_charset.condition()));

    if (consume)
    {
        value = content;
        if (consume)
        {
            tokenizer._location.count (this->_keyword);
            tokenizer._ptr += this->_keyword.length();

            tokenizer._location.count (content);
            tokenizer._ptr += content.length();
        }        
    }
    return true;
}

/********************************************************************************/ 
/*                                                                              */ 
/*              accept any length between two keywords                          */ 
/*  userfull for comment like <!-- xml comment -->                              */ 
/*                                                                              */ 
/********************************************************************************/ 

keyword_to_keyword_parser::keyword_to_keyword_parser(const std::string &start, const std::string &end) :
       _start(start)
    ,  _end(end)
{ }
keyword_to_keyword_parser::~keyword_to_keyword_parser()
{ }

bool keyword_to_keyword_parser::read (tokenizer& tokenizer, any& value, bool consume) const
{
	if (! prefix(tokenizer._ptr,this->_start.c_str()))
        return false;

    const char* pstart = tokenizer._ptr + this->_start.length();
    const char* p = pstart;
    p += this->_start.length();

    while (! prefix(p, this->_end.c_str()))
        ++p;

    if (consume)
    {
        value = std::string(pstart, p);
        tokenizer._location.count (this->_start);
        tokenizer._ptr += this->_start.length();

        tokenizer._location.count(pstart, p);
        tokenizer._ptr += std::distance(pstart, p);

        tokenizer._location.count (this->_end);
        tokenizer._ptr += this->_end.length();
    }
    return true;
}

//end of file
