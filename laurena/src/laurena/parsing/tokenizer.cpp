///
/// \file     tokenizer.cpp
/// \brief    A tokenizer class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A tokenizer class
///

#include <laurena/toolboxes/loader.hpp>
#include <laurena/algorithm/strings/readinteger.hpp>

#include <laurena/parsing/tokenizer.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>
#include <laurena/memory/memory_functions.hpp>

using namespace laurena;


tokenizer::tokenizer()
{    
    this->_ptr = nullptr ;
}

tokenizer::~tokenizer()
{ }

void tokenizer::load(const std::string& filename)
{
    _source = loader<>::load(filename);
    this->_location.reset ();
    this->_location.filename (filename);
    this->_ptr = this->_source.c_str();
}
void tokenizer::str(const char* source)
{
    this->_source = source;
    this->_location.reset ();
    this->_location.filename (std::string("<null>")) ;
    this->_ptr = this->_source.c_str();
}


int32 tokenizer::readExpected(any& value, const parsers& ps, const boost::dynamic_bitset<>& allowed)
{
    word32 sz = ps.size();

    for ( word32 i = 0 ; i < sz; i ++)
    {
        if (allowed.test(i))
        if ( ps [i]-> read(*this,value,true))
            return i;
    }
    return -1;
}
int32 tokenizer::readExpected(any& value, const parsers& ps, const boost::dynamic_bitset<>& tabs, word8 expected)
{
    word32 sz = ps.size();
    word32 i;

    while (*this->_ptr)
    {

        for ( i = 0 ; i < sz; i ++)
        {
            if (tabs.test(i) || i == expected)
            if ( ps [i]->read(*this,value,true))
            {
                if (i == expected)
                    return i;

                break;
            }
            
        }
        if (i == sz)
            return -1;
    }
    return -1;    
}

std::ostream& tokenizer::prefixErrorMessage(std::ostream& message) const 
{
    message << "Syntax error in "
                      << this->_location.filename()
                      << " at line "
                      << this->_location.line ()
                      << " : "
                      << this->_location.column  ()
                      << ", " ;
    return message;
}

void tokenizer::syntaxError (const std::string& message) const
{
    std::ostringstream msg;
    this->prefixErrorMessage(msg);
    msg << message;
    throw LAURENA_FAILED_PARSING_EXCEPTION(msg.str().c_str(),this->_ptr);
}

void tokenizer::skipCurrentLine ()
{
const char* p = this->_ptr ;
    while (*p && *p != '\n' )
        p++;

    if (*p == '\n' )
    {
        p++;
        word32 sz = std::distance(this->_ptr,p);
        this->_location.count(this->_ptr,this->_ptr + sz);
        this->_ptr += sz;
    }

}

void tokenizer::skipUntil (const char* keyword, bool skipKeyword)
{
const char* p = strstr(this->_ptr,keyword);

    if (p)
    {       
        word32 sz = std::distance(this->_ptr,p);
        if (skipKeyword)
            sz += strlen(keyword);

        this->_location.count(this->_ptr,this->_ptr + sz);
        this->_ptr += sz;
    }
}

tokenizer& tokenizer::restore(const tokenizer::state& s)
{
    if (s._source != this->_source.c_str())
        throw LAURENA_EXCEPTION("Source has been modified and state can't be restored");

    this->_ptr = s._ptr;
    return *this;
}

/********************************************************************************/ 
/*                                                                              */ 
/*      operator >> functions                                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
tokenizer& tokenizer::operator >> (const char c)
{
    if ( *this->_ptr == c)
    {
        ++this->_ptr ;
        this->_location.count(c);

    } 
    else 
    {
        char b [ 2 ] = "a";
        *b = c;
        std::string message = "Was expecting character '" ;
        message.append(b).append("'");
        this->syntaxError(message);
    }
    return *this;
}

tokenizer& tokenizer::operator >> (int32& i)
{
    std::string svalue = std::move(readinteger(this->_ptr));
    word32 v = svalue.length();
    if (v)
	{
        i = boost::lexical_cast<int32,std::string>(svalue);
		this->_ptr += svalue.length();
		this->_location.count(svalue);
	}
    else
        this->syntaxError("Was expecting a signed integer");
    return *this;
}

tokenizer& tokenizer::operator >> (word32& w)
{
	std::string svalue = std::move(readinteger(this->_ptr));
	word32 v = svalue.length();
    if (v)
	{
        w = boost::lexical_cast<word32,std::string>(svalue);     
		this->_ptr += svalue.length();
		this->_location.count(svalue);
	}
    else
        this->syntaxError("Was expecting a signed integer");
    return *this;
}

tokenizer& tokenizer::operator>>  (int16& i)
{
	std::string svalue = std::move(readinteger(this->_ptr));
	word32 v = svalue.length();
    if (v)
	{
        i = boost::lexical_cast<int16,std::string>(svalue);       
		this->_ptr += svalue.length();
		this->_location.count(svalue);
	}
    else
        this->syntaxError("Was expecting a signed integer");
    return *this;
}

tokenizer& tokenizer::operator>>  (word16& w)
{
	std::string svalue = std::move(readinteger(this->_ptr));
	word32 v = svalue.length();
    if (v)
	{
        w = boost::lexical_cast<word16,std::string>(svalue);       
		this->_ptr += svalue.length();
		this->_location.count(svalue);
	}
    else
        this->syntaxError("Was expecting a signed integer");
    return *this;
}



//end of file