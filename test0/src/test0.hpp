/********************************************************************************/ 
/*  classic C includes                                                          */ 
/********************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>


#if defined(_WIN32)

// Windows Only
#include <crtdbg.h>
//#include <windows.h>

#else

// supposed linux
#include <limits.h>
#include <unistd.h>
#endif

/********************************************************************************/ 
/*      STL includes                                                            */ 
/********************************************************************************/ 
#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream> 
#include <list>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <typeindex>			// used in classes.hpp
