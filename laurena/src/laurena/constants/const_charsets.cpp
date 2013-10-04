///
/// \file     const_charsets.cpp
/// \brief    Global character set constants
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Global character set constants
///

#include <laurena/constants/const_charsets.hpp>

using namespace laurena;

charset laurena::CHARSET_RN = "\r\n" ;
charset laurena::CHARSET_TABS = "\r\n\t ";
charset laurena::CHARSET_TABS2 = "\r\t ";
charset laurena::CHARSET_VARNAME = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_" ;
charset laurena::CHARSET_IDNAME  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/" ;
charset laurena::CHARSET_FULLPATH_FILENAME_SEPARATOR = "/\\:" ;
charset laurena::CHARSET_NUMBER  = "0123456789"  ;
charset laurena::CHARSET_LOWCASE = "abcdefghijklmnopqrstuvwxyz" ;
charset laurena::CHARSET_HEXANUMBER = "0123456789abcdefABCDEF";
charset laurena::CHARSET_LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
charset laurena::CHARSET_BINARY = "01" ;
charset laurena::CHARSET_ACCENTS = "יטךכאגהןמüûצפח" ;
charset laurena::CHARSET_URI = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-/?=&%";

//End of file
