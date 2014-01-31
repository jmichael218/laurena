///
/// \file     vector_descriptor.hpp
/// \brief    Describe a serializable std::vector<T> class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Describe a serializable std::vector<T> class
///

#ifndef LAURENA_VECTOR_DESCRIPTOR_H
#define LAURENA_VECTOR_DESCRIPTOR_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/traits/type_traits.hpp>

#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>

#include <laurena/descriptors/classes.hpp>
#include <laurena/descriptors/standard_class_descriptor.hpp>
#include <laurena/descriptors/features/container_feature.hpp>
#include <laurena/types/literator.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/ 
/*          base_list_container_feature                                          */ 
/*********************************************************************************/
class base_vector_container_feature : public container_feature
{
public:

    /****************************************************************************/ 
    /*                                                                          */
    /****************************************************************************/ 
    base_vector_container_feature(const descriptor* listDescriptor, const descriptor* elementDescriptor, bool areElementsPointer = false);

    /****************************************************************************/ 
    /*          virtual functions from container_feature                        */ 
    /****************************************************************************/ 
    virtual bool                        hasKey()                const;

    virtual const descriptor*           elementDescriptor()     const ;
    virtual const descriptor*           keyDescriptor()         const ;

	virtual bool						areElementsPointers()   const;

protected:

    const descriptor*                   _list_descriptor;
    const descriptor*                   _elements_descriptor;
    bool                                _are_elements_pointer;
};


template<typename CONTAINER, typename ELEMENT>
class vector_container_feature : public base_vector_container_feature
{
public:

    vector_container_feature(const descriptor* vectorDescriptor, const descriptor* elementDescriptor) 
        : base_vector_container_feature (vectorDescriptor, elementDescriptor, boost::is_pointer<ELEMENT>::value)
        { }

    /****************************************************************************/ 
    /*          virtual functions from container_feature                        */ 
    /****************************************************************************/ 
    virtual literator    begin(const any& container)    const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);        
        return literator (new vector_literator<CONTAINER,ELEMENT>(c));
    }
    virtual literator    end(const any& container)      const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);
        return literator(new vector_literator<CONTAINER,ELEMENT>(c,c->end()));
    }
    

    virtual void push(any& container, any& element) const
    {
        CONTAINER* c = anycast<CONTAINER*>(container);
        c->push_back(anycast<ELEMENT>(element));
        
    }

    virtual void set(any& container, const any& key, any& element) const
    {
		CONTAINER* c = anycast<CONTAINER*>(container);
		word32 index = anycast<word32>(key);
		if (index >= c->size())
			c->resize(index+1);

		if (boost::is_pointer<ELEMENT>::value || element.desc()->has(descriptor::Flags::ATOMIC))
			(*c) [index] = anycast<ELEMENT>(element);
		else
		{
			ELEMENT* e = anycast<ELEMENT*>(element);
			(*c) [index] = *e ;
		}

		
	}

    virtual void get(any& container, const any& key, any& element) const
    {
		CONTAINER* c = anycast<CONTAINER*>(container);
		word32 index = anycast<word32>(key);

		if (boost::is_pointer<ELEMENT>::value)
			element = (*c) [index];
		else
			element = & (*c) [index];
    }

};

/*********************************************************************************/
/*          list_descriptor                                                      */ 
/*********************************************************************************/ 


template<typename CONTAINER,typename ELEMENT>
class vector_descriptor : public standard_class_descriptor<CONTAINER>
{
public:

    /****************************************************************************/ 
    /*          constructors, desctructor                                       */ 
    /****************************************************************************/ 
    vector_descriptor(const char* name, const descriptor* parent = nullptr) 

    :   standard_class_descriptor<CONTAINER>(name, parent) ,
        _container_class_feature (this,classes::byType(typeid(typename traits<ELEMENT>::basetype)))
    { }


    /****************************************************************************/ 
    /*          virtual functions from descriptor                               */ 
    /****************************************************************************/ 
    virtual const class_feature*   feature(Feature featureId) const
    {
        return (featureId == Feature::CONTAINER ? &this->_container_class_feature : this->standard_class_descriptor<CONTAINER>::feature(featureId)) ;
    }

	/****************************************************************************/ 
	/*			static functions												*/ 
	/****************************************************************************/ 
	static vector_descriptor<CONTAINER,ELEMENT>* build(const char* name, const descriptor* parentClassDescriptor=nullptr)
	{
		auto cd = new vector_descriptor<CONTAINER,ELEMENT>(name, parentClassDescriptor );
        cd->constructor([](){return new CONTAINER;});
        classes::add(cd);        

		// getter for the vector size
		field::getter getsize = [] (const any& object, any& value) { CONTAINER* c = anycast<CONTAINER*>(object); value = c->size(); };

		// setter for the vector size
		field::setter setsize = [] (any& object, const any& value) { CONTAINER* b = anycast<CONTAINER*>(object); b->resize(anycast<word32>(value));};

		field& f = cd->template addField<word32>("size", setsize, getsize);
		
		f.supportTag("vector.size");

        return cd;
	}

    /****************************************************************************/ 
    /*          protected data                                                  */ 
    /****************************************************************************/ 
    protected:
    vector_container_feature<CONTAINER,ELEMENT>      _container_class_feature;
    
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif