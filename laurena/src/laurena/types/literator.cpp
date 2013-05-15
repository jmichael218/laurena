///
/// \file     literator.cpp
/// \brief    An enhanced iterator<forward_iterator_tag,any> that wrap other iterators
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///   An enhanced iterator<forward_iterator_tag,any> that wrap other iterators
///
#include <laurena/types/literator.hpp>

using namespace laurena;

literator::literator () : std::iterator<std::forward_iterator_tag,any> () , _iterator(nullptr)
{ }

literator::literator (const literator& source) : std::iterator<std::forward_iterator_tag,any> () , _iterator(source._iterator ? source._iterator->clone() : nullptr )
{ }

literator::literator (wrapped_iterator* it) : std::iterator<std::forward_iterator_tag,any> (), _iterator(it)
{ }

literator::~literator ()
{
    delete this->_iterator;
}

literator& literator::operator++()
{
    if ( this->_iterator )
        this->_iterator->next();
    return *this;
}

any literator::operator*() const
{
    any a;
    
    return this->_iterator ? this->_iterator->get(a) : a ;
}

any literator::key() const
{
    any a;
    return this->_iterator ? this->_iterator->key(a) : a;
}

literator& literator::operator=(const literator& source)
{
    if (this->_iterator)
        delete this->_iterator;
    this->_iterator = source._iterator->clone();
    return *this;
}

bool literator::operator==(const literator& source) const
{
    return this->_iterator ? ( this->_iterator->equals(source._iterator)) : false;
}

bool literator::operator!=(const literator& source) const
{    
    return !(*this == source);
}
//End of file

    