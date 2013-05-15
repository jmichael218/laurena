///
/// \file       string_array.cpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      A vector<string> container with enhanced methods.
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A vector<string> container with enhanced methods.
///

#include <laurena/types/string_array.hpp>
#include <laurena/memory/memory_functions.hpp>

using namespace laurena;


/********************************************************************************/ 
/*                                                                              */ 
/*                 code for class string_array                                   */ 
/*                                                                              */ 
/********************************************************************************/ 
string_array::string_array() : std::vector<std::string> ()
{
    this->_attributes = nullptr;
}

string_array::string_array(const char* keywordList,word8 separator)
{
    this->_attributes = nullptr;
    this->set (keywordList,separator) ;
}

string_array::string_array(const string_array& object) :
    std::vector<std::string>(object)
    
{  
    this->_attributes = object._attributes;
}

void string_array::set(const char* keywordList, word8 separator)
{
const word8* p;
const word8* p2;
word16 nbKeywords = 1, sizeKeyword, idx=0;

    // clear the array
    this->clear();

    // count how many space there is in the text
    p = (const word8*) keywordList ;
    while (*p) 
    {
        if ( *(p++) == separator ) 
            ++nbKeywords;        
    }

    // reinitialize it
    this->resize(nbKeywords);

    // parse string
    p = (const word8*) keywordList ;       
    p2 = p ;
    while (*p2 )
    {
        if ( *p2 == separator )
        {
            sizeKeyword = memory::offset(p,p2) ;
            this->operator[](idx++).assign ( (const char*) p , sizeKeyword ) ;
            p = p2+1 ;
        }                    
        ++p2 ;    
    }
    sizeKeyword = memory::offset(p,p2) ;
    this->operator[] (idx++).assign ( (const char*) p , sizeKeyword ) ;    

    assert(idx==nbKeywords) ;
}

void string_array::all (const std::string& value)
{
    for(std::string& s : *this)
		s = value;    
}

    /// \brief find without lower/upper case difference
int32 string_array::find(const std::string& value) const
{
    int32 sz = (int32) this->size();
    int32 i = sz-1;
    while(i > -1)   
    {
        if (boost::iequals(this->operator[](i),value))
            return i;
        --i;
    }
    return -1;
}

    ///
    /// \brief find exact value
    /// 
int32 string_array::findExact(const std::string& value) const
{
    int32 sz = (int32) this->size();
    int32 i = sz-1;
    while(i > -1)
    {
        if (this->operator[] (i) == value)
            return i;
        i--;
    }
    return -1;
}

std::string string_array::concat(const std::string& delimiter) const
{
    std::ostringstream os;

    for (word32 i = 0 ; i < this->size(); ++i)
    {
        os << (i==0? "" : delimiter) << this->operator[](i);
    }
    return os.str();
}

void string_array::attributes(const string_array* attributesArray) 
{ 
    this->_attributes = attributesArray ; 
    if ( this->size() < this->_attributes->size())
        this->resize(this->_attributes->size());
}

//end of file
