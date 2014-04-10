///
/// \file     polymorphic_feature.cpp
/// \brief    Interface of a polymorphic feature for a class
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Interface of a polymorphic feature for a class
///
#include <laurena/descriptors/features/polymorphic_feature.hpp>
#include <laurena/exceptions/null_pointer_exception.hpp>
#include <laurena/descriptors/features/class_features.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*          code for PolymorphicClassFeatureImpl                                */ 
/*                                                                              */ 
/********************************************************************************/ 

polymorphic_feature::polymorphic_feature(const descriptor* desc, const descriptor* parentDescriptor)
                            : class_feature(desc) , _parent(parentDescriptor) , _children (nullptr)
{ }

polymorphic_feature::~polymorphic_feature()
{
    if (_children)
    {
        delete _children;
        _children = nullptr;
    }
}

bool polymorphic_feature::has_parent () const
{
    return (_parent != nullptr);
}

void polymorphic_feature::addChildClass (const descriptor* child_class)
{
    if (this->_children == nullptr)
        this->_children = new std::list<const descriptor*>();

    this->_children->push_back(child_class);
}

const descriptor& polymorphic_feature::parent() const
{
    if (_parent == nullptr)
        throw LAURENA_NULL_POINTER_EXCEPTION("class doesn't have any parent.");
    else
        return *_parent;
}


bool polymorphic_feature::isParentClass(const descriptor& childClass) const
{
    const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(childClass.feature(Feature::POLYMORPHIC));
    if (!pcf)
        return false;

    if (!pcf->has_parent())
        return false;

    return ( (pcf->parent().name()) == this->desc().name()) ? true : this->isParentClass(pcf->parent());
}