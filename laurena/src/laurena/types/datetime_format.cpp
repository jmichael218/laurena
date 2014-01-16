///
/// \file     dateformat.cpp
/// \brief    A datetime format class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   A datetime format class
///
#include <laurena/types/datetime_format.hpp>
#include <laurena/debug/debug.hpp>

using namespace laurena;


/********************************************************************************/ 
/*                                                                              */ 
/*      code for class DateFormat                                               */ 
/*                                                                              */ 
/********************************************************************************/ 
datetime_format::datetime_format () : _months(12), _months_abbrev(12), _days(7), _days_abbrev(7)
{
	
}

inline word32 DateFormatCountChar(const char* p,char symbol)
{
    word32 res = 0 ;
    while (*p++ == symbol ) res ++ ;
}

word64 datetime_format::epoch  (const std::string& source, const std::string& format)
{
	char s [ 10 ];
    std::istringstream ss (source) ;
    const char* pstr = format.c_str() , *p ;

    char cformat ;
    word32 count ;

    word32 year = 0 , month = 0 , day = 0 , hours = 0 , minutes = 0 , seconds = 0 ;
    while (*pstr)
    {
        count = 0 ; 
        cformat = *pstr  ;
        
        count = 1; p = pstr ;
        while ( *p++ == cformat ) count ++ ;

        if ( cformat == 'y' )
        {
            if ( count >= 4 )
            {
                ss.read(s, 4);
				year = boost::lexical_cast<word16,const char*>(s);
                pstr += 4 ;
            } else if ( count >= 2 )
            {
                ss.read(s, 2);
				year = 1900 + boost::lexical_cast<word16,const char*>(s);
                pstr += 2 ;
            }
        } 
		else if ( cformat == 'm' )
        {
            if ( count >= 2)
            {
                ss.read(s, 2);
				month = boost::lexical_cast<word16,const char*>(s) - 1;
                pstr += 2 ;
            } else if ( count == 1 )
            {
                assert(false);
            }
        }
        else if ( cformat == 'D' )
        {
            if ( count >= 2 )
            {
                ss.read(s, 2);
				day = boost::lexical_cast<word16,const char*>(s) - 1;
                pstr += 2 ;
            }
            else if ( count == 1 )
            {
                assert(false);
            }
        } else
        {
            ss.ignore(1);
            pstr ++ ;
        }          
    }
    struct tm t ;
   
    t.tm_year = year - 1900 ;
    t.tm_mon  = month ;
    t.tm_mday = day ;
    t.tm_hour = hours ;
    t.tm_min  = minutes ;
    t.tm_sec  = seconds ;
    return mktime (&t ) ;
    
}

std::string datetime_format::format (word64 epoch,const std::string& format)
{
std::ostringstream ss;

time_t tt = ( time_t ) epoch ;
struct tm* t = localtime (&tt) ;

const char* pstr = format.c_str() , *p ;
    
char c ;
word32 count;

    while ( *pstr )
    {
        c = *pstr  ;      
        count = 1; p = pstr + 1 ;
        while ( *p++ == c ) count ++ ;
        
        /****************************************************************************/ 
        /*              Format year                                                 */ 
        /****************************************************************************/ 

        if ( c == 'y' )
        {
            if ( count >= 4 )
            {
                count = 4 ;
                ss << ( t->tm_year + 1900 ) ; 
                

            } else if ( count >=2 )
            {
                count = 2 ;
                word32 year = t->tm_year % 100 ;

                if ( year == 0 ) 
					ss << "00" ;
                else 
                {
                    if ( year < 10 ) ss << "0" ;
                    ss << year ;
                }
            } else count = 0 ;
            
        } 

        /****************************************************************************/ 
        /*              Format month                                                */ 
        /****************************************************************************/
        else if ( c == 'm' )
        {

            if ( count >= 4 )
            {
                count = 4 ;
				ss << this->_months [ t->tm_mon ];                                
            } 
            else if ( count == 3 )
            {
                ss <<  this->_months_abbrev [ t->tm_mon ]; 
            }
            else if ( count == 2 )
            {
                word32 month = t->tm_mon + 1 ;
                ss << ( month < 10 ? "0" : "" ) << month ;
            }
            else if ( count == 1 )
            {
                ss << ( t->tm_mon + 1 ) ;
            }
            else count = 0 ;
        } 

        /****************************************************************************/ 
        /*          Format day in month                                             */ 
        /****************************************************************************/      
        else if ( c == 'd' )
        {
            if ( count >= 2 )
            {
                count = 2 ;
                word32 day = t->tm_mday ;
                ss << ( day < 10 ? "0" : "" ) << day ;
            } else if ( count == 1 )
            {
                ss << t->tm_mday ;
            } 
            else count = 0 ;
        } 
        else 
        {
            count = 0 ;
        }
        
        
        if (count)
			pstr += count ; //<! Don't do pstr ++ since internal buffer _data value can be changed if string is extended
		else
			ss.write(&c, 1);

    }    

    // Return
    return ss.str();    
        
}
