///
/// \file       any.hpp
/// \copyright  (C) Copyright 2002-2012 Frederic Manisse
/// \brief      An extended version of boost::any with class descriptor info
/// \author     Frederic Manisse
/// \version    1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// An extended version of boost::any with class descriptor info
///

#ifndef LAURENA_ANY_H
#define LAURENA_ANY_H

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
#include <laurena/traits/basetype.hpp>
#include <laurena/traits/voidptr.hpp>

#include <laurena/exceptions/exception.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/*********************************************************************************/
/*          class any                                                            */ 
/*********************************************************************************/ 

class any
{

    /****************************************************************************/ 
    /*      protected sub classes                                               */ 
    /****************************************************************************/ 
    protected:

    /*
        \brief base class for any's templated content.
    */ 
    class base_content
    {
        public: 
            base_content (const descriptor* d = nullptr) : _descriptor(d) {}
            virtual ~base_content() {}

         public: 
            virtual const std::type_info &      type()      const = 0;
            virtual base_content*               clone()     const = 0;
            virtual void*                       ptr()       const = 0;
            inline const descriptor*            desc()      const           { return this->_descriptor; }

        protected:
            const descriptor*     _descriptor;

    };

    
    /*
        \brief templated content class
    */ 
    template<typename VALUETYPE>
    class content : public base_content
    {
        public: 

        /************************************************************************/ 
        /*              constructor, destructors                                */ 
        /************************************************************************/ 
            
		content (const VALUETYPE & value, const descriptor* d=nullptr) : base_content (d) , _value(value)  {} ;
		virtual ~content () {} ;

        /************************************************************************/ 
        /*              virtual functions from base_content                     */ 
        /************************************************************************/ 

		virtual const std::type_info &      type()      const		 { return typeid(VALUETYPE); }
		virtual base_content *              clone()     const		 { return new content<VALUETYPE>( this->_value, this->_descriptor); }
		virtual void*                       ptr()       const        { return voidptr<VALUETYPE>::cast(this->_value); }

        /************************************************************************/ 
        /*              datas                                                   */ 
        /************************************************************************/ 
        public: 

        VALUETYPE                  _value;

        /************************************************************************/ 
        /*              other stuff                                             */ 
        /************************************************************************/ 
        private: // intentionally left unimplemented
        
        base_content & operator=(const base_content &);

    };



    /****************************************************************************/ 
    /*          CONSTRUCTOR, DESTRUCTOR                                         */ 
    /****************************************************************************/ 

    public:

	any();
    any(const char* str);
	any(const any& other);
	any(any&& other);

	template<typename VALUETYPE> any (const VALUETYPE & value)  : 
		_content(new content<VALUETYPE>(value , classes::byType(typeid(typename basetype<VALUETYPE>::type)))) 
	{ }

	virtual ~any();

	/****************************************************************************/
	/*			OPERATORS														*/ 
	/****************************************************************************/

    template<typename VALUETYPE>
    any & operator=(const VALUETYPE & value)
    {

        const descriptor* cd = classes::byType(typeid(typename basetype<VALUETYPE>::type));
        if (!cd)
            cd = classes::byType(typeid(VALUETYPE));
        if (!cd)
            throw new LAURENA_EXCEPTION("can't find a class descriptor for this type.");

		if (_content)
            delete _content;
        _content = new content<VALUETYPE>(value,cd);

        return *this;
    }

    any& operator=(const any& value);
	any& operator=(any&& value);

	bool operator==(const any& value);

    inline bool operator != (const any& value)		 { return  ! this->operator== (value) ; }

    /****************************************************************************/ 
    /*          METHODS                                                         */ 
    /****************************************************************************/ 
    public: 

	std::string tos () const;			
    
    inline any& clear ()
    {
		if (_content)
            delete _content;            
        return *this;
    }   


    inline bool isEmpty() const						{ return !_content; }

    void* ptr() const
    {
        if (!_content)
        {
            throw new LAURENA_EXCEPTION("empty content cannot be casted to a pointer.");
        }
        return _content->ptr();
    }

    inline const std::type_info & type() const
    {
        return _content ? _content->type() : typeid(void);
    }


 
    inline const descriptor* desc() const
    {
        return _content ? _content->desc() : nullptr ;
    }

    /****************************************************************************/ 
    /*                  protected datas                                         */ 
    /****************************************************************************/ 
    protected:
        base_content * _content;

    /****************************************************************************/ 
    /*                  friend zone                                             */ 
    /****************************************************************************/ 
    private: // representation

        template<typename VALUETYPE> friend VALUETYPE * anycast(any *);
        template<typename VALUETYPE> friend VALUETYPE * dynamic_anycast(any*) ;
};

/****************************************************************************/ 
/*          casts                                                           */ 
/****************************************************************************/ 
template<typename VALUETYPE>
VALUETYPE* dynamic_anycast(any* operand)
{
    const descriptor* ocd = operand->desc();
    if (!ocd)
        return 0;

    const descriptor* vcd = classes::byType(typeid(typename basetype<VALUETYPE>::type));
    if (!vcd)
        return 0;

    return classes::areParents(*ocd,*vcd) ?  &static_cast<any::content<VALUETYPE> *>(operand->_content)->_value : 0;
}

template<typename VALUETYPE>
VALUETYPE * anycast(any * operand)
{
    VALUETYPE* res = operand && operand->type() == typeid(VALUETYPE) ? 
            &static_cast<any::content<VALUETYPE> *>(operand->_content)->_value
        : dynamic_anycast<VALUETYPE>(operand) ;

    if (res == 0)
    {
        const type_info& operand_info = operand->type();
        const char* operand_name = operand_info.name();
        const type_info& valuetype_info = typeid(VALUETYPE);
        const char* valuetype_name = valuetype_info.name();
        std::string message = "Failed to cast from '";
        message.append(operand_name).append ("' to '").append(valuetype_name).append("'.");
        //throw new LAURENA_STANDARD_EXCEPTION(message.c_str());
    }

    return res;
}  

template<typename VALUETYPE>
inline const VALUETYPE * anycast(const any * operand)
{
    return anycast<VALUETYPE>(const_cast<any *>(operand));
}

template<typename VALUETYPE>
VALUETYPE anycast(any & operand)
{
    typedef typename boost::remove_reference<VALUETYPE>::type nonref;

    nonref * result = anycast<nonref>(&operand);
    if(!result)
        throw new LAURENA_EXCEPTION("anycast failed");

    return *result;
}

template<typename VALUETYPE>
inline VALUETYPE anycast(const any & operand)
{
    typedef typename boost::remove_reference<VALUETYPE>::type nonref;

    return anycast<const nonref &>(const_cast<any &>(operand));
}


/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif