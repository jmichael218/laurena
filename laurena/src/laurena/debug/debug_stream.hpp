///
/// \file     debug_stream.hpp
/// \brief    An ostream writing output on the debug interface
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An ostream writing output on the debug interface
///

#ifndef LAURENA_DEBUG_STREAM_H
#define LAURENA_DEBUG_STREAM_H

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
/*              debug_stream                                                    */ 
/********************************************************************************/ 
class debug_stream_sink {
public:

    // Necessary for boost iostreams
    typedef char                            char_type;
    typedef boost::iostreams::sink_tag      category;

    std::streamsize write(const char* s, std::streamsize n);
};


class debug_stream : public boost::iostreams::stream<debug_stream_sink>
{
public:

    debug_stream ();    
    virtual ~debug_stream ();

protected:

    debug_stream_sink         _sink;    
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
