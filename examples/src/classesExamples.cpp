///
/// \file     classesExamples.cpp
/// \brief    Classes for JSON examples
/// \author   Frederic Manisse
/// \version  1.0
///
/// Classes for JSON examples
///
#include <laurena/laurena.hpp>
#include <laurena/json/json.hpp>

#include "classesExamples.hpp"

using namespace laurena;

void buildClassDescriptor_SimpleCat ()
{

    // create class descriptor for the class 'cat'
	// syntax to create a class descriptor for a simple class made of POD fields is standard_class_descriptor<CLASS>::build("classname");
	// calling ::build will also add the class descriptor to the global classes list.
    auto d = standard_class_descriptor<simple_cat>::build("simple_cat");

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
    d->addField(&simple_cat::_name,"name");
    d->addField(&simple_cat::_age,"age");
	d->addField(&simple_cat::_birds,"birds");
	d->addField(&simple_cat::_mouses,"mouses");
}

void buildClassDescriptor_Animal()
{
    // create class descriptor for the class 'animal'
	auto d_animal = standard_class_descriptor<animal>::build("animal");
	d_animal->addField(&animal::_specie,"specie");
    d_animal->addField(&animal::_name,"name");
    d_animal->addField(&animal::_age,"age");
}

void buildClassDescriptor_Cat()
{
	// create class descriptor for the class 'cat'
	// it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", classes::byName("animal"));

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
    d->addField(&cat::_age,"age");
	d->addField(&cat::_birds,"birds");
	d->addField(&cat::_mouses,"mouses");
}

void buildClassDescriptor_Zoo()
{
	auto d_zoo = list_descriptor<zoo,animal>::build("zoo");
}

void buildClassDescriptor_Circus()
{
	auto d = vector_descriptor<circus,animal>::build("circus");
}

string_array genders = "male female" ;
string_array user_types = "student professor visitor" ;

void buildClassDescriptor_User()
{
    // create class descriptor for the class 'user'
	auto d = standard_class_descriptor<user>::build("user");
	d->addField(&user::_gender,"gender").isEnum(genders);
    d->addField(&user::_type,"type").isEnum(user_types);
	d->addField(&user::_age,"age");
	d->addField(&user::_name,"name");
}

string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;
void buildClassDescriptor_Dragon()
{
    // create class descriptor for the class 'dragon'
	auto d = standard_class_descriptor<dragon>::build("dragon");
	d->addField(&dragon::_name,"name");
	d->addField(&dragon::_state,"state").isBitSet(dragon_states);
	d->addField(&dragon::_foods,"food").isBitSet(dragon_foods);
}

void buildClassDescriptor_Building()
{
	auto d = standard_class_descriptor<building>::build("building");

	field::getter sgname = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->name(); };
	field::setter ssname = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->name(anycast<const std::string&>(value));};
	d->init_virtual_field("name",std::string,ssname,sgname);

	field::getter sgfloors = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->floors(); };
	field::setter ssfloors = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->floors(anycast<unsigned char>(value));};
	d->init_virtual_field("floors",unsigned char,ssfloors, sgfloors);
}

std::ostream& operator << (std::ostream& dest, const ivertex& v)
{
    return dest << "(" << v._x << "," << v._y << ")" ;
}

tokenizer& operator >> (tokenizer& source, ivertex& v)
{
    return source >> '(' >> v._x >> ',' >> v._y >> ')' ;
}

void buildClassDescriptor_IVertex()
{
	auto d = standard_class_descriptor<ivertex>::build("ivertex");
    d->addField(&ivertex::_x,"x");
    d->addField(&ivertex::_y,"y");
	d->annotate(new format("json",new generic_writer<ivertex> () , new generic_parser<ivertex> () ));
}


void buildClassDescriptor_ITriangle()
{
	auto d = standard_class_descriptor<itriangle>::build("itriangle");
	d->addField(&itriangle::_v0,"v0");
	d->addField(&itriangle::_v1,"v1");
	d->addField(&itriangle::_v2,"v2");
};

//End of file
