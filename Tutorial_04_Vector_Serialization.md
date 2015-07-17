Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t04_vector_example/main.cpp

## A Vector Class ##

This example describes how to build descriptor for vector containers based on the std::vector template class.

It is pretty much the same than for the list example.


## The classes ##

Here are our classes : soldier for the object class, armyr for the vector < soldier > class and squad for the vector < soldier `*` > class:

```
// Here is our 'soldier' class
class soldier
{
public:

    std::string     _rank;    //<! Soldier rank or occupation like 'sergeant' or 'sniper'
    std::string     _name;    //<! Name of the soldier
    unsigned char   _age;     //<! Age of the soldier, in years

    bool operator == (const soldier& source)
    { return this->_rank == source._rank && this->_name == source._name && this->_name == source._name; }
};

// Here is our vector class : the army class which is a list of soldier
class army : public std::vector<soldier>
{
};

// Here is our list class with pointers to soldiers
class squad : public std::vector<soldier*>
{
};

```

## Build the descriptors ##

This is pretty much like the list example :

```
// This function register the soldier class to the serialization and parsing system
void build_soldier_descriptor ()
{
    // create class descriptor for the class 'soldier'
    auto d = standard_class_descriptor<soldier>::build("soldier");
    d->add_field(&soldier::_rank,"rank");
    d->add_field(&soldier::_name,"name");
    d->add_field(&soldier::_age,"age");
}

// This function register the army class to the serialization and parsing system
// 'army' is a container of soldier
void build_army_descriptor()
{
	auto d = list_descriptor<army,soldier>::build("army");
}

// This function register the squad class to the serialization and parsing system
// 'squad' is a container of pointer to soldiers
void build_squad_descriptor()
{
	auto d = list_descriptor<squad,soldier*>::build("squad");
}
```


### Serialization of a vector < podclass > ###

Let's build our army example:

```
    army z;

    soldier a;
    a._rank = "Elite Private";
    a._name   = "John Rambi";
    a._age    = 17;
    z.push_back (a);

    a._rank   = "Elite Private";
    a._name   = "Chuck Norras";
    a._age    = 45;
    z.push_back (a);

    a._rank = "Captain";
    a._name   = "James T Kirk" ;
    a._age    = 32;
    z.push_back(a);
```

Let's serialize it :

```
	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned cat :
	std::cout << "Here is my army:" << std::endl << destination << std::endl;
```

We get the following output :

```
Here is my army:
{
	"army":
	[

		{

			"rank": "Elite Private",
			"name": "John Rambi",
			"age": "17"
		},
		{

			"rank": "Elite Private",
			"name": "Chuck Norras",
			"age": "45"
		},
		{

			"rank": "Captain",
			"name": "James T Kirk",
			"age": "32"
		}
	]
}
```

Let's marshall it in a new instance of the army class :

```
	army z2;
	json::json::parse(destination,z2);

	std::cout << "Cloned soldiers in my duplicated army are : " ;
	for (soldier an : z2) 
            std::cout << an._name << ", " ;
	std::cout << std::endl ;

```

We get the following output :

```
Cloned soldiers in my duplicated army are : John Rambi, Chuck Norras, James T Kirk, 
```

### Serialization of a vector of object pointers ###

Laurena"s library would also work with pointers to serializable objects because, as in the list example, serializable class descriptors can create new instance of an object.

Therefore, let's build our squad :

```
    squad z;

    soldier a;
    a._rank = "Sniper";
    a._name   = "Walter Jones";
    a._age    = 27;
    z.push_back (&a);

    soldier b;
    b._rank = "Sergeant";
    b._name   = "Gerald Magh";
    b._age    = 45;
    z.push_back (&b);

    soldier c;
    c._rank = "Major";
    c._name   = "Lee Smith" ;
    c._age    = 32;
    z.push_back(&c);
```

Let's serialize it :

```
	// Let's serialize it into json
	std::string destination = json::json::serialize(z);

	// Let's display my jsoned squad:
	std::cout << "Here is my squad:" << std::endl << destination << std::endl;
```

We get the following output :

```
Here is my squad:
{
	"squad":
	[

		{

			"rank": "Sniper",
			"name": "Walter Jones",
			"age": "27"
		},
		{

			"rank": "Sergeant",
			"name": "Gerald Magh",
			"age": "45"
		},
		{

			"rank": "Major",
			"name": "Lee Smith",
			"age": "32"
		}
	]
}
```

Let's marshall it in a new instance of the squad class :

```
	// Now let's instancing the squad
	squad z2;
	json::json::parse(destination,z2);

	std::cout << "Soldiers in my duplicated squad are : " ;
	for (soldier* an : z2) 
           std::cout << an->_name << ", " ;
	std::cout << std::endl ;
```

We get the following output :

```
Soldiers in my duplicated squad are : Walter Jones, Gerald Magh, Lee Smith, 
```
Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t04_vector_example/main.cpp