/// \file     annotation.cpp
/// \brief    A base class for annotations
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  A base class for annotations
///

#include <laurena/descriptors/annotation.hpp>
#include <laurena/descriptors/descriptable.hpp>

using namespace laurena;

annotation::annotation(const char* name) : _name (name), _descriptable (nullptr)
{ }

annotation::annotation(const std::string& name) : _name (name), _descriptable (nullptr)
{ }

annotation::~annotation ()
{ }

const descriptable* annotation::annotates () const { return this->_descriptable; }

annotations_map::annotations_map () : std::unordered_map<std::string,annotation*> (), _own_annotations(false)
{}

annotations_map::~annotations_map ()
{
	if (this->_own_annotations)
	{
		annotations_map::iterator i;
		annotation* a ;

		while ((i=this->begin()) != this->end())
		{
			a = i->second;
			this->erase(i);
			delete a;
		}
	}

}

const annotation* annotations_map::get(const std::string& key) const
{
	auto i = this->find(key);
	return (i == this->end()) ? nullptr : i->second;
}
//End of file
