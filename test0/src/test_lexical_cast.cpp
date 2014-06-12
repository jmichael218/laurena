#include "test0.hpp"
#include <laurena/casting/lexical_cast.hpp>
#include <utility>

void testNotPossibleCast()
{
    // double to pair for example
    
    /*
    std::pair<int, int> a;
    int b ;
    
    try
    {
        b = laurena::lexical_cast<int>(a);
    }
    catch(const std::runtime_error& oor)
    {
        std::cout << oor.what() << std::endl;
    }
    */
    
}

void testToString()
{
    int b = 9;
    std::string s = laurena::lexical_cast<std::string>(b);
    std::cout << "lexical_cast<std::string, int> (9) = " << s << std::endl;
    
    unsigned int ui = UINT_MAX;
    s = laurena::lexical_cast<std::string>(ui);
    std::cout << "lexical_cast<std::string, unsigned int>(UINT_MAX) = " << s << std::endl;
    
}

void testFromString()
{
    std::string ss = "9";
    
    int i = laurena::lexical_cast<int>(ss);
    i = laurena::lexical_cast_impl<int, std::string>::cast(ss);
    std::cout << "laurena::lexical_cast<int>(\"9\") =" << i << std::endl;
}

void testLexicalCast()
{
    testNotPossibleCast();
    testToString();
    testFromString();
}