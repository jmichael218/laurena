/// \file     any_descriptor.hpp
/// \brief    A special class descriptor for laurena::any
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A special class descriptor for laurena::any
///

#ifndef LAURENA_ANY_DESCRIPTOR_H
#define LAURENA_ANY_DESCRIPTOR_H

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

#include <laurena/descriptors/classes.hpp>
#include <laurena/traits/laurena_traits.hpp>
#include <laurena/descriptors/features/any_feature.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/ 
/*          ClassFeatureImpl                                                     */ 
/*********************************************************************************/ 
class any_feature_impl : public any_feature
{
public:

    any_feature_impl(const descriptor* desc);
    virtual ~any_feature_impl() {}

    /****************************************************************************/ 
    /*          any-typed   class functions                                     */ 
    /****************************************************************************/ 
    //!brief return true if the class is a generic class accepting any type of content, like boost::any
    virtual bool isAny () const ;

    //!brief return the true type of the current content.
    virtual const descriptor& desc(void* ptrValue) const;

    //!brief return true if any content is empty
    virtual bool isEmpty (void* ptrValue) const ;    


};

/*********************************************************************************/
/*          ClassDescriptor                                                      */ 
/*********************************************************************************/ 
class any_descriptor : public descriptor {
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    any_descriptor();
    


    /****************************************************************************/ 
    /*          virtual functions from class_descriptor                         */ 
    /****************************************************************************/ 

    // ACCESSOR
    virtual const class_feature* feature(Feature featureId) const;

    // RAW VALUE SERIALIZATION 
    //! unserialize a value into memory
    virtual void set(void* ptr, const any& value) const;

    //! serialize a value into memory
    virtual any& get(void* ptr, any& value) const;


    // TO/FROM STRING SERIALIZATION 
    //! Serialization to a string     
    virtual std::string atos(const any& value) const;

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    any_feature_impl     _any_class_feature;
};

template<> 
struct td<any>
{
    static const descriptor* desc()
    {
        static const descriptor* res = NULL;
        if (res == NULL)
        {
            res = new any_descriptor();
            classes::add(res);
        }

        return res;
    }
};
/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif