///
/// \file     literator.hpp
/// \brief    An enhanced iterator<forward_iterator_tag,any> that wrap other iterators
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   An enhanced iterator<forward_iterator_tag,any> that wrap other iterators
///

#ifndef LAURENA_ITERATOR_WRAPPER_H
#define LAURENA_ITERATOR_WRAPPER_H

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

#include <laurena/types/any.hpp>
/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*      Iterator wrapper                                                        */ 
/********************************************************************************/ 

class wrapped_iterator 
{
    public:
    virtual ~wrapped_iterator() {}

    /****************************************************************************/ 
    /*          virtual function that must be implemented                       */ 
    /****************************************************************************/ 
    virtual wrapped_iterator*      clone()=0;
    virtual any& get(any& value)          =0;
    virtual any& key(any& value)          =0;
    virtual void next()                   =0;
    virtual bool equals(wrapped_iterator* source) const = 0;    
};

template<typename CONTAINER, typename ELEMENT>
class list_literator : public wrapped_iterator
{
    public:

    typedef typename CONTAINER::iterator iterator;
    virtual ~list_literator() {}

    /****************************************************************************/ 
    /*          constructor                                                     */ 
    /****************************************************************************/ 
    list_literator(CONTAINER* list) : _list(list), _iterator(list->begin()) {}
    list_literator(CONTAINER* list, iterator it) : _list(list), _iterator(it) {}

    /****************************************************************************/ 
    /*          virtual functions implemented                                   */ 
    /****************************************************************************/ 
    virtual wrapped_iterator* clone() 
    {
        list_literator<CONTAINER,ELEMENT>* ret = new list_literator<CONTAINER,ELEMENT>(this->_list, this->_iterator);
        return ret;
    }    

    virtual any& get(any& value)
    {
        return value = *(this->_iterator);
    }

    virtual void next()
    {
        this->_iterator++;
    }

    virtual bool equals(wrapped_iterator* source) const
    {
        list_literator<CONTAINER,ELEMENT>* casted = dynamic_cast<list_literator<CONTAINER,ELEMENT>*>(source);
        return casted ? ( casted->_iterator  == this->_iterator && casted->_list == this->_list ) : false;
    }

    virtual any& key(any& value)
    {
        throw new LAURENA_EXCEPTION("Lists doesn't have keys");
    }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    iterator     _iterator;
    CONTAINER*   _list;
};

template<typename CONTAINER, typename ELEMENT>
class vector_literator : public wrapped_iterator
{
    public:

    typedef typename CONTAINER::iterator iterator;
    virtual ~vector_literator() {}

    /****************************************************************************/ 
    /*          constructor                                                     */ 
    /****************************************************************************/ 
    vector_literator(CONTAINER* vector) : _vector(vector), _iterator(vector->begin()) {}
    vector_literator(CONTAINER* vector, iterator it) : _vector(vector), _iterator(it) {}

    /****************************************************************************/ 
    /*          virtual functions implemented                                   */ 
    /****************************************************************************/ 
    virtual wrapped_iterator* clone() 
    {
        vector_literator<CONTAINER,ELEMENT>* ret = new vector_literator<CONTAINER,ELEMENT>(this->_vector, this->_iterator);
        return ret;
    }    

    virtual any& get(any& value)
    {
        return value = *(this->_iterator);
    }

    virtual void next()
    {
        this->_iterator++;
    }

    virtual bool equals(wrapped_iterator* source) const
    {
        vector_literator<CONTAINER,ELEMENT>* casted = dynamic_cast<vector_literator<CONTAINER,ELEMENT>*>(source);
        return casted ? ( casted->_iterator  == this->_iterator && casted->_vector == this->_vector ) : false;
    }

    virtual any& key(any& value)
    {
        word32 index = this->_iterator - this->_vector->begin();
        return value = index;
    }

    /****************************************************************************/ 
    /*          protected datas                                                 */ 
    /****************************************************************************/ 
    protected:

    iterator     _iterator;
    CONTAINER*   _vector;
};

class literator : public std::iterator<std::forward_iterator_tag,any>
{
public:
   
    /****************************************************************************/ 
    /*      constructor, destructor                                             */ 
    /****************************************************************************/ 
    literator () ;
    literator (const literator& source);
    literator (wrapped_iterator* it);
    ~literator ();

    /****************************************************************************/ 
    /*      iterator functions                                                  */ 
    /****************************************************************************/
    literator& operator++();
    any operator*() const;
    any key() const;
    literator& operator=(const literator& source);
    bool operator==(const literator& source) const;
    bool operator!=(const literator& source) const;
    
    /****************************************************************************/ 
    /*      protected content                                                   */ 
    /****************************************************************************/ 
    wrapped_iterator*          _iterator;
};


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 
}
#endif
