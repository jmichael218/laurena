///
/// \file     list_descriptor.hpp
/// \brief    Describe a serializable std::list<T> class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable std::list<T> class
///

#ifndef LAURENA_LIST_DESCRIPTOR_H
#define LAURENA_LIST_DESCRIPTOR_H

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
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/descriptors/features/container_feature.hpp>
#include <laurena/types/literator.hpp>
#include <laurena/traits/basetype.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/ 
/*          base_list_container_feature                                          */ 
/*********************************************************************************/
class base_list_container_feature : public container_feature
{
public:

    /****************************************************************************/ 
    /*                                                                          */
    /****************************************************************************/ 
    base_list_container_feature(const descriptor* listDescriptor, const descriptor* elementDescriptor, bool areElementsPointer = false);

    /****************************************************************************/ 
    /*          virtual functions from container_feature                        */ 
    /****************************************************************************/ 
    virtual bool                        hasKey()                const;

    virtual const descriptor*           elementDescriptor()     const ;
    virtual const descriptor*           keyDescriptor()         const ;

	virtual bool						areElementsPointers()   const;

    virtual void set(any& container, const any& key, any& element) const;
    virtual void get(any& container, const any& key, any& element) const;

protected:

    const descriptor*                   _list_descriptor;
    const descriptor*                   _elements_descriptor;
    bool                                _are_elements_pointer;
};


template<typename CONTAINER, typename ELEMENT>
class list_container_feature : public base_list_container_feature
{
public:

    list_container_feature(const descriptor* listDescriptor, const descriptor* elementDescriptor) 
        : base_list_container_feature (listDescriptor, elementDescriptor, boost::is_pointer<ELEMENT>::value)
        { }

    /****************************************************************************/ 
    /*          virtual functions from container_feature                        */ 
    /****************************************************************************/ 
    virtual literator    begin(const any& container)    const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);        
        return literator (new list_literator<CONTAINER,ELEMENT>(c));
    }
    virtual literator    end(const any& container)      const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);
        return literator(new list_literator<CONTAINER,ELEMENT>(c,c->end()));
    }
    

    virtual void push(any& container, any& element) const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);
        c->push_back(anycast<ELEMENT>(element));
        
    }

};

/*********************************************************************************/
/*          list_descriptor                                                      */ 
/*********************************************************************************/ 


template<typename CONTAINER,typename ELEMENT>
class list_descriptor : public standard_class_descriptor<CONTAINER>
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    list_descriptor(const char* name, word8 nbFields=0, const descriptor* parent = nullptr) 

    :   standard_class_descriptor<CONTAINER>(name,nbFields,parent) ,
        _container_class_feature (this,classes::byType(typeid(typename basetype<ELEMENT>::type)))
    { }


    /****************************************************************************/ 
    /*          virtual functions from descriptor                               */ 
    /****************************************************************************/ 
    virtual const class_feature*   feature(Feature featureId) const
    {
        return (featureId == Feature::CONTAINER ? &this->_container_class_feature : this->standard_class_descriptor<CONTAINER>::feature(featureId)) ;
    }


    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    protected:
    list_container_feature<CONTAINER,ELEMENT>      _container_class_feature;
    
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif