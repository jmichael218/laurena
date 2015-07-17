# Private or protected field #

When your class does have private or protected field, the macros init\_field to build the field descriptor doesn't work.

To serialize your field through Laurena, you can use, if they exist, getters and setters.

Let's use this example class :

```
class building
{
public:

	building () : _floors(1), _name() {}
	
	inline void floors (unsigned char value)	{ this->_floors = value; }
	inline const unsigned char floors () const  { return this->_floors;}

	inline void name(const std::string& value)  { this->_name = value; }
	inline const std::string& name() const      { return this->_name; }

protected:
	unsigned char	_floors;
	std::string	_name;
};
```

You won't be able to build a class descriptor the same way you did in the previous example using the init\_field function. However, you can use get and set functions like **const std::string& name() const** and **void name(const std::string& value)** to write and read the _**name** field._

## Declare getter and setter for a field descriptor ##

You have to create std::function object which match field::setter and field::getter signature, using **any** objects. ( See [AnyClass](AnyClass.md) ) :

```
typedef std::function<void(const any& obj, any& value)> getter;
typedef std::function<void(any& obj, const any& value)> setter;

```

So, for our **building** class, we create setters and getters this way, using lambda functions :

```
// getter for the _name field
field::getter sgname = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->name(); };

// setter for the _name field
field::setter ssname = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->name(anycast<const std::string&>(value));};

// getter for the _floors field
field::getter sgfloors = [] (const any& object, any& value) { building* b = anycast<building*>(object); value = b->floors(); };

// setter for the _floors field
field::setter ssfloors = [] (any& object, const any& value) { building* b = anycast<building*>(object); b->floors(anycast<unsigned char>(value));};
```

Then we build the class descriptor, but instead of using **init\_field**, we use **init\_virtual\_field(fieldname, field typename, setter, getter)**

```
	auto d = standard_class_descriptor<building>::build("building");
	d->init_virtual_field("name",std::string,ssname,sgname);
	d->init_virtual_field("floors",unsigned char,ssfloors, sgfloors);

```

## The class descriptor in action ##

The use of a such class descriptor is the same than in any other example :

```
	building b;
	b.name ("Town House");
	b.floors(3);

	// Let's serialize it into json
	std::string destination = json::json::serialize(b);

	// Let's display my jsoned building :
	std::cout<< "Here is my building details:" << std::endl << destination << std::endl;
```

will display:

```
Here is my building details:
{
	"building":
	{

		"name": "Town House",
		"floors": 3
	}
}
```

and

```
	// let's create a new building from the serialized one
	building b2;
	json::json::parse(destination,b2);

	std::cout<< "Building 2 is '" << b2.name() << "' and has " << ((int)b2.floors()) << " floors." << std::endl;
```

will display:

```
Building 2 is 'Town House' and has 3 floors.
```