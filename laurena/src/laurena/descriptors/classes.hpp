///
/// \file     Classes.hpp
/// \brief    Manager of serializable classes descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Manager of serializable classes descriptors
///
#ifndef LAURENA_CLASSES_H
#define LAURENA_CLASSES_H

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

#include <laurena/descriptors/descriptor.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              global classes descriptor management                            */ 
/********************************************************************************/ 
class classes 
{

    /****************************************************************************/ 
    /*          public datas                                                    */ 
    /****************************************************************************/     
    public:

    static void add(const descriptor* myClass);
    static const descriptor*  byName (const std::string& name);
    static const descriptor*  byType (const type_info& type);

    /****************************************************************************/ 
    /*          tool functions                                                  */ 
    /****************************************************************************/ 
    static void logClasses ();
    static bool areParents(const descriptor& c1, const descriptor& c2);

    static void init ();

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/
    protected:    

    static std::unordered_map<std::string,const descriptor*>      _classes_by_name;
    static std::unordered_map<word64,const descriptor*>           _classes_by_typeid;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
