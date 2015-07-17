Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t10_xml_serialization/main.cpp

## Introduction ##

This tutorial is a simple example to explain how to use the xml language instead of the json language.

## Classes descriptors ##

Let's use the classes from example 2. There is no need to modify anything. A same class descriptor can be used with all supported language. There is no need to create a class descriptor for each language.

```
// This function register the animal class to the serialization and parsing system
void build_animal_descriptor ()
{
    // create class descriptor for the class 'animal'
    auto d_animal = standard_class_descriptor<animal>::build("animal");
    d_animal->add_field(&animal::_specie,"specie");
    d_animal->add_field(&animal::_name,"name");
    d_animal->add_field(&animal::_age,"age");
}


// This function register the cat class to the serialization and parsing system
void build_cat_descriptor ()
{
    // create class descriptor for the class 'cat'
    // it is pretty much the same than for simple classes except you give the parent class in the creation
    auto d = standard_class_descriptor<cat>::build("cat", td<animal>::desc());
    d->add_field(&cat::_birds,"birds");
    d->add_field(&cat::_mouses,"mouses");
}
```

## Serialization ##

Serialization of a C++ object in XML is pretty much the same than with JSON :

```
    // let's create a cat
    cat kitty;
    kitty._name = "Kitty";
    kitty._age  = 5;
    kitty._birds = 4;
    kitty._mouses = 14;

    // Let's serialize it into json
    std::string destination = xml::xml::serialize(kitty);

    // Let's display my jsoned cat :
    std::cout << "Here is my cat details:" << std::endl << destination << std::endl;
```

The output is :
```
Here is my cat details:
<cat>
  <specie>cat</specie>
  <name>Kitty</name>
  <age>5</age>
  <birds>4</birds>
  <mouses>14</mouses>
</cat>
```

## Marshalling ##
To create a C++ object from a XML bloc, follow the same guildeline than for JSON:

```
    // let's create a new cat from our serialized kitty 
    cat kimmie;
    xml::xml::parse(destination,kimmie);
    std::cout << "Kimmie is a " << kimmie._specie << " named " << kimmie._name 
         << ", has " << ((int)kimmie._age) << " years, killed " 
         << kimmie._birds << " birds and " << kimmie._mouses << " mouses." 
         << std::endl;
```

and as expected, we get the following output :
```
Kimmie is a cat named Kitty, has 5 years, killed 4 birds and 14 mouses.
Kimmie is a clone of Kitty !!
Laurena's serialization works fine !
```

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t10_xml_serialization/main.cpp