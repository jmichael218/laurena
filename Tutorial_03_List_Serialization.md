Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t03_list_example/main.cpp

## A List Class ##

This example describes how to build descriptor for list container based on the std::list template class.


## The classes ##

Here are our classes : animal and zoo:

```
class animal
{
public:

	std::string		_specie;
	std::string		_name;
	unsigned char	_age;

	bool operator == (const animal& source)
	{ return this->_age == source._age && this->_specie == source._specie && this->_name == source._name; }

	animal& operator = (const animal& source)
	{ this->_age = source._age ; this->_specie = source._specie; this->_name = source._name; return *this; }
};

class zoo : public std::list<animal>
{
};

```

## Build the descriptors ##

We already built the class descriptor for the animal class, so here is only how to build a class descriptor for a list container :

```
	auto d_zoo = list_descriptor<zoo,animal>::build("zoo");

```

Yes, that's all ...

### Let's serialize and parse ###

Let's build our zoo :

```
	zoo z;

	animal a;
	a._specie = "lion";
	a._name   = "Rutger";
	a._age    = 7;
	z.push_front (a);

	a._specie = "elephant";
	a._name   = "Dora";
	a._age    = 45;
	z.push_front (a);

	a._specie = "crocodile";
	a._name   = "James" ;
	a._age    = 12;
	z.push_front(a);
```

Let's serialize it :

```
	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned cat :
	std::cout << "Here is my zoo:" << std::endl << destination << std::endl;
```

We get the following output :

```
Here is my zoo:
{
	"zoo":
	[

		{

			"specie": "crocodile",
			"name": "James",
			"age": 12
		},
		{

			"specie": "elephant",
			"name": "Dora",
			"age": 45
		},
		{

			"specie": "lion",
			"name": "Rutger",
			"age": 7
		}
	]
}
```

Let's marshall it in a new instance of the zoo class :

```
	// Now let's instancing the new zoo
	zoo z2;
	json::json::parse(destination,z2);

	std::cout << "Animals in my other zoo are : " ;
	for (animal an : z2) 
            std::cout << an._name << ", " ;
	std::cout << std::endl ;

```

We get the following output :

```
Animals in my other zoo are : James, Dora, Rutger,
```

## If elements are pointer ##

Laurena"s library would also work if our list class was defined like this :

```
class circus : public std::list<animal*>
{
};

auto d = list_descriptor<circus,animal*>::build("circus");

```

The animal descriptor, when built, create a default constructor for the "animal" class. Therefore, the library is able to create new elements for a list. You will have to code the circus class destructor to free the elements because Laurena doesn't trace objects created.

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t03_list_example/main.cpp