///
/// \file     bitset_descriptor.hpp
/// \brief    A special class descriptor for boost::dynamic_bitset
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable class composed of serializable fields 
///

#ifndef LAURENA_BITSET_DESCRIPTOR_H
#define LAURENA_BITSET_DESCRIPTOR_H

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/classes.hpp>
#include <laurena/traits/laurena_traits.hpp>

#include <boost/dynamic_bitset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          bitset_descriptor                                                    */ 
/*********************************************************************************/ 
class bitset_descriptor : public descriptor {
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    bitset_descriptor();


    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 

	//ACCESSORS
	virtual any& clear(any& value) const;
	virtual bool has(descriptor::Flags flag) const;

	//CAST
	virtual any cast (const any& value) const;

	// OPERATORS
	virtual bool equals(const any& a0, const any& a1) const;

    // RAW VALUE SERIALIZATION
    virtual void            set(void* ptr, const any& value)  const;
    virtual any&            get(void* ptr, any& value)  const;

    // TO/FROM STRING SERIALIZATION 
    virtual std::string     atos(const any& value) const;
	virtual any&            stoa(const std::string& string_value, any& value) const;    
    
    // OBJECT CONSTRUCTOR FOR INJECTION 
    virtual any create() const;
    

};

template<> 
struct td<boost::dynamic_bitset<> >
{
    static const descriptor* desc();
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//End of file
