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
    d->add_field(&simple_cat::_name,"name");
    d->add_field(&simple_cat::_age,"age");
	d->add_field(&simple_cat::_birds,"birds");
	d->add_field(&simple_cat::_mouses,"mouses");
}

void buildClassDescriptor_Animal()
{
    // create class descriptor for the class 'animal'
	auto d_animal = standard_class_descriptor<animal>::build("animal");
	d_animal->add_field(&animal::_specie,"specie");
    d_animal->add_field(&animal::_name,"name");
    d_animal->add_field(&animal::_age,"age");
}

void buildClassDescriptor_Cat()
{
	// create class descriptor for the class 'cat'
	// it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", classes::byName("animal"));

	// to be able to serialize fields, call descriptor->init_field(CLASS,"fieldname",field)
	d->add_field(&cat::_birds,"birds");
	d->add_field(&cat::_mouses,"mouses");
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
	d->add_field(&user::_gender,"gender").annotate(new format_enum("format.all",genders));
    d->add_field(&user::_type,"type").annotate(new format_enum("format.all",user_types));
	d->add_field(&user::_age,"age");
	d->add_field(&user::_name,"name");
}

string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;
void buildClassDescriptor_Dragon()
{
    // create class descriptor for the class 'dragon'
	auto d = standard_class_descriptor<dragon>::build("dragon");
	d->add_field(&dragon::_name,"name");
	d->add_field(&dragon::_state,"state").annotate(new format_bitset("format.all", dragon_states));
	d->add_field(&dragon::_foods,"food").annotate(new format_bitset("format.all", dragon_foods));
}

void buildClassDescriptor_Building()
{
	auto d = standard_class_descriptor<building>::build("building");

	field::getter sgname = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->name(); };
	field::setter ssname = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->name(anycast<const std::string&>(value));};
	d->add_field<std::string>("name", ssname,sgname);

	field::getter sgfloors = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->floors(); };
	field::setter ssfloors = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->floors(anycast<unsigned char>(value));};
	d->add_field<unsigned char>("floors", ssfloors, sgfloors);
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
    d->add_field(&ivertex::_x,"x");
    d->add_field(&ivertex::_y,"y");

	d->annotate(new generic_format<ivertex>("json"));
}


void buildClassDescriptor_ITriangle()
{
	auto d = standard_class_descriptor<itriangle>::build("itriangle");
	d->add_field(&itriangle::_v0,"v0");
	d->add_field(&itriangle::_v1,"v1");
	d->add_field(&itriangle::_v2,"v2");
};

//End of file
