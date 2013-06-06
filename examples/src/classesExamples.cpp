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
    d->init_field(simple_cat,"name",_name);
    d->init_field(simple_cat,"age",_age);
	d->init_field(simple_cat,"birds",_birds);
	d->init_field(simple_cat,"mouses",_mouses);
}

void buildClassDescriptor_Animal()
{
    // create class descriptor for the class 'animal'
	auto d_animal = standard_class_descriptor<animal>::build("animal");
	d_animal->init_field(animal,"specie",_specie);
    d_animal->init_field(animal,"name",_name);
    d_animal->init_field(animal,"age",_age);
}

void buildClassDescriptor_Cat()
{
	// create class descriptor for the class 'cat'
	// it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", classes::byName("animal"));

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
    d->init_field(cat,"age",_age);
	d->init_field(cat,"birds",_birds);
	d->init_field(cat,"mouses",_mouses);
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
	d->init_field(user,"gender",_gender).isEnum(genders);
    d->init_field(user,"type",_type).isEnum(user_types);
	d->init_field(user,"age",_age);
	d->init_field(user,"name",_name);
}

string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;
void buildClassDescriptor_Dragon()
{
    // create class descriptor for the class 'dragon'
	auto d = standard_class_descriptor<dragon>::build("dragon");
	d->init_field(dragon,"name",_name);
	d->init_field(dragon,"state",_state).isBitField(dragon_states);
	d->init_field(dragon,"food",_foods).isBitField(dragon_foods);
}
//End of file
