///
/// \file     testunit.cpp
/// \brief    A static class to store test stats and macros to write quickly tests
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A static class to store test stats and macros to write quickly tests
///
#include <laurena/debug/testunit.hpp>

using namespace laurena;


word32 testunit::_tests = 0;  // number of test started
word32 testunit::_ok   = 0;  // number of test succesfull
word32 testunit::_nok  = 0;  // number of test failed
std::ostream* testunit::_log = nullptr; // log used

void testunit::start(const char* testmessage)
{
    ++_tests;
    if (_log)
        (*_log) << "  " << testmessage << " ...";
}

bool testunit::end(bool ok)
{
    if (ok)
    {
        ++_ok;
        if (_log)
            (*_log) << "OK" << std::endl;
    }
    else
    {
        ++_nok;
        if (_log)
            (*_log) << "NOK" << std::endl;
    }
    return ok;
}

void testunit::setLogger(std::ostream* log)
{
    _log = log;
}

void testunit::function(const char* function)
{
    if(_log)
        (*_log) << "*" << std::endl << "* Testing " << function << ":" << std::endl << "*" << std::endl;
}

void testunit::type(const char* typeName)
{
    if(_log)
    {
        (*_log) << "*************************************************************************" << std::endl ;
        (*_log) << "*";
        word32 sz = strlen(typeName);
        word32 tabs = sz >= 57 ? 0 : ((57 - sz) >> 1);
        for (word32 u = 0 ; u < tabs ; ++u)
            _log->put(' ');
        (*_log) << "TESTING CLASS " << typeName ;
        tabs = 57 - tabs - sz;

        if ( tabs > 57 ) 
            tabs = 0;

        for (word32 u = 0 ; u < tabs ; ++u)
            _log->put(' ');
        (*_log) << "*" << std::endl;
        (*_log) << "*************************************************************************" << std::endl ;
    }
}

void testunit::displayResults()
{
    if(_log)
    {
        (*_log) << _tests << " tests started." << std::endl
                << (_ok + _nok) << " tests completed." << std::endl
                << _ok << " tests OK." << std::endl
                << _nok << " tests FAILED." << std::endl;
        

    }

}
//end of file

