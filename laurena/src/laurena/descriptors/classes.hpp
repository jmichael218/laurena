///
/// \file     Classes.hpp
/// \brief    Manager of classes descriptors
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Manager of classes descriptors
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

//! \brief Manager for all class descriptors
//!
//! 'classes' is a static class with std::map to index all class descriptors created.
//! Descriptor registered here can be used anywhere in the serialization process, 
//! when they are searched by name or by type_info.
class classes 
{

    /****************************************************************************/ 
    /*          public datas                                                    */ 
    /****************************************************************************/     
    public:

	//! \brief Register a new class descriptor
	//! \param desc : The descriptor to register
	//!
	//! This function register a new class descriptor for a global use.
	//! It will erase previous class  descriptor object with same name or with same type_info
    static void add(const descriptor* desc);

	//! \brief Find a class descriptor using name as search parameter.
	//! \param name : The class name registered when descriptor was built
	//! \return : nullptr if no class registered with this name, otherwhile a const ptr to the descriptor
	//!
	//! This static function search for a class descriptor by its name.
	//! The name must match the string parameter used as 'name' when the descriptor was built.
	//! The function return nullptr if no class found.
    static const descriptor*  by_name (const std::string& name);

	//! \brief Find a class descriptor using is type_info as search parameter.
	//! \param type : The type_info registered when descriptor was built
	//! \return : nullptr if no class registered with this type, otherwhile a const ptr to the descriptor
	//!
	//! This static function search for a class descriptor by the type_info of the described class.	
	//! The function return nullptr if no class found.
    static const descriptor*  by_type (const type_info& type);
	

    /****************************************************************************/ 
    /*          tool functions                                                  */ 
    /****************************************************************************/ 
	//! \brief Send a list of all registered class names on a output stream
	//! \param destination : output stream
	//!
	//! This function exists for debug purpose. 
	//! It list names of all registered classes.
    static void log_classes (std::ostream& destination);

	//! \brief check if classes are related through polymorphism.
	//! \param c1 : first class
	//! \param c2 : second class
	//!
	//! The function return true if c1 and c2 are related through polymorphism.
	//! In a C++ way, it means c1 can be dynamic_casted to c2 or than c2 can be dynamic_casted to c1.
    static bool are_parents(const descriptor& c1, const descriptor& c2);

	//! \brief Register class descriptors for basic types and laurena inner types.
	//! 
	//! This function must be called before any operations related to the laurena library.
	//! It creates and registers class descriptors for basic types like std::string or int, 
	//! but also for laurena inner types like stringarray or variable.
    static void init ();

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/
    protected:    

	//! \brief map of class descriptors, indexed by class name.
    static std::unordered_map<std::string,const descriptor*>	_classes_by_name;		

	//! \brief map of class descriptors, indexed by type_index. See std::type_index
    static std::unordered_map<size_t,const descriptor*>         _classes_by_typeid;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
