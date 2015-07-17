Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t02_polymorphic_example/main.cpp

## A Polymorphic Class ##

This example describes how to build descriptor for polymorphic classes, i.e a parent class and a child class.


## The classes ##

Here are our classes : animal and cat :

```
class animal
{
public:

	std::string		_specie;
	std::string		_name;
	unsigned char	_age;

	bool operator == (const animal& source)
	{ return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }
};

class cat : public animal
{
public:

	unsigned int	_birds;
	unsigned int	_mouses;

	cat () : animal () 
	{ this->_specie = "cat" ;  }

	bool operator==(const cat& c)
	{ return this->animal::operator==(c) && this->_birds == c._birds && this->_mouses == c._mouses ; }
};
```

## Build the descriptors ##

This is pretty much the same than for the previous example, except we pass the parent class when we build the child class :

```
    // create class descriptor for the class 'animal'
    auto d_animal = standard_class_descriptor<animal>::build("animal");
    d_animal->add_field(&animal::_specie,"specie");
    d_animal->add_field(&animal::_name,"name");
    d_animal->add_field(&animal::_age,"age");

    // Creating class descriptor for the class 'cat'
    // It is pretty much the same than for simple classes except we need to 
    // pass the parent class descriptor as second parameter to standard_class_descriptor::build
    // To get the descriptor of any registered class, use td<CLASS>::desc() 
    // Therefore, to get cat's class parent descriptor, we use td<animal>::desc()
    auto d = standard_class_descriptor<cat>::build("cat", td<animal>::desc());
    d->add_field(&cat::_birds,"birds");
    d->add_field(&cat::_mouses,"mouses");
```

### Let's serialize and parse ###

Let's create a cat the same way we did for the previous example.

```
	// let's create a cat
	cat kitty;
	kitty._name = "Kitty";
	kitty._age  = 5;
	kitty._birds = 4;
	kitty._mouses = 14;

	// Let's serialize it into json
	std::string destination = json::json::serialize(kitty);

	// Let's display my jsoned cat :
	std::cout << "Here is my cat details:" << std::endl << destination << std::endl;
```

We get the following output :

```
Here is my cat details:
{
	"cat":
	{

		"specie": "cat",
		"name": "Kitty",
		"age": 5,
		"age": 5,
		"birds": 4,
		"mouses": 14
	}
}
```

Then we parse our result to recreate a cat. We use the same code than for the previous example except we will display the specie.

```
	// let's create a new cat from our serialized kitty 
	cat kimmie;
	json::json::parse(destination,kimmie);
	std::cout << "Kimmie is a " << kimmie._specie << " named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

	if (kimmie == kitty)
		std::cout << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
	else
		std::cout << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;

```

and we get :
```
Kimmie is a cat named Kitty, has 5 years, killed 4 birds and 14 mouses.
Kimmie is a clone of Kitty !!
Laurena's serialization works fine !
```

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t02_polymorphic_example/main.cpp