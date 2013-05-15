///
/// \file     debug_stream.cpp
/// \brief    An ostream writing output on the debug interface
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An ostream writing output on the debug interface
///
#include <laurena/debug/debug_stream.hpp>
#include <laurena/debug/debug.hpp>

using namespace laurena;

std::streamsize debug_stream_sink::write(const char* s, std::streamsize n)
{
    std::string s2(s,(size_t)n);
    debug::println(s2);

    return n;
}

debug_stream::debug_stream () : 
boost::iostreams::stream<debug_stream_sink> ()
{
    this->open(_sink);
    this->set_auto_close(false);
}

debug_stream::~debug_stream ()
{

}

//End of file
