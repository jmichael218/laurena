# A simple example #

This example shows how to set up a class descriptor for a simple class with POD field members.

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t01_simple_example/main.cpp

# A cat class #

Let's make a class to describe little cats :
```
class cat 
{
public:

	std::string	_name;
	unsigned char	_age;
	unsigned int	_birds;
	unsigned int	_mouses;

	bool operator==(const cat& c)
	{
		return this->_name == c._name && this->_age == c._age && this->_birds == c._birds && this->_mouses == c._mouses ;
	}
};
```

Now let's create a cat

```
	cat kitty;
	kitty._name = "Kitty";
	kitty._age  = 5;
	kitty._birds = 4;
	kitty._mouses = 14;
```

# A class descriptor #

Let's create the class descriptor

```
    // create class descriptor for the class 'cat'
    // syntax to create a class descriptor for a simple class made of POD fields is standard_class_descriptor<CLASS>::build("classname");
    // calling ::build will also add the class descriptor to the global classes list.
    auto d = standard_class_descriptor<simple_cat>::build("simple_cat");

	// to be able to serialize fields, call descriptor->add_field(POINTER_TO_FIELD, "fieldname")
    d->add_field(&simple_cat::_name,"name");
    d->add_field(&simple_cat::_age,"age");
    d->add_field(&simple_cat::_birds,"birds");
    d->add_field(&simple_cat::_mouses,"mouses");

    // That's all. Now cat class is serializable in and from any supported language !
```

# Serialization #

```
    // Let's serialize poor kitty into a json
    std::string destination = json::json::serialize(kitty);

    // Let's display my jsoned cat :
    cout << "Here is my cat details:" << std::endl << destination << std::endl;
```

And we get:

```
Here is my cat details:
{
	"cat":
	{

		"name": "Kitty",
		"age": 5,
		"birds": 4,
		"mouses": 14
	}
}
```

Let's parse this result into a new cat:

```
	// let's create a new cat from our serialized kitty 
	cat kimmie;
	json::json::parse(destination,kimmie);
	std::cout << "Kimmie is named " << kimmie._name << ", has " << ((int)kimmie._age) << " years, killed " << kimmie._birds << " birds and " << kimmie._mouses << " mouses." << std::endl;

	if (kimmie == kitty)
		std::cout << "Kimmie is a clone of Kitty !!" << std::endl << "Laurena's serialization works fine !" << std::endl;
	else
		std::cout << "Kimmie is different of Kitty !!" << std::endl << "Laurena's serialization is a fake !" << std::endl ;
```

And we finally get:

```
Kimmie is named Kitty, has 5 years, killed 4 birds and 14 mouses.
Kimmie is a clone of Kitty !!
Laurena's serialization works fine !
```

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t01_simple_example/main.cpp