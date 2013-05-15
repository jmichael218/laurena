///
/// \file     testunit.hpp
/// \brief    A static class to store test stats and macros to write quickly tests
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A static class to store test stats and macros to write quickly tests
///

#ifndef LAURENA_TEST_UNIT_H
#define LAURENA_TEST_UNIT_H

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

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              interface                                                       */ 
/********************************************************************************/ 
class testunit {
    
    public:

    static void type(const char* typeName);
    static void function(const char* function);
    static void startTest(const char* testmessage);

    //! return ok
    static bool endTest (bool ok);
    static void setLogger(std::ostream* log);
    inline static std::ostream& log() { return *_log; }

    static void displayResults();

    static word32 tests() { return _tests ; }
    static word32 oks  () { return _ok; }
    static word32 noks () { return _nok; }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:
    static word32           _tests ;  // number of test started
    static word32           _ok    ;  // number of test succesfull
    static word32           _nok   ;  // number of test failed
    static std::ostream*    _log   ; // log used

};

#define TEST_UNIT_CONDITION(code,testmessage) try { testunit::startTest(testmessage); bool testUnitResult = (code); testunit::endTest(testUnitResult);} catch (...) {testunit::endTest(false);}

#define TEST_UNIT_EXCEPTION(code,testmessage,exceptionType) try { testunit::startTest(testmessage); code; testunit::endTest(false);} catch (const exceptionType&) {testunit::endTest(true);} catch (...) {testunit::endTest(false);}

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
