## Setting a numeric field as a bitset ##

Laurena support serialization and marshalling for the class boost::dynamic\_bitset<>.

Also some unsigned integer fields are sometimes bitsets, as in our example class below.

```
class dragon 
{
public:

	dragon () : _state(0), _name() { _foods.resize(5); };

	unsigned char		_state;	// masks are 1 for 'happy', 2 for 'hungry', 4 for 'sleepy'
	boost::dynamic_bitset<>	_foods; // 0 for knight, 1 for princess, 2 for cow, 3 for peasant, 4 for horse
	std::string		_name;
};
```

For example, if our dragon is sleepy and hungry, then we will have dragon._state = 2 + 4 = 6._

Laurena does have a mechanism so such field are serialized and marshalled as a string value made of concatenated keywords separated by a space.

For example, instead of serializing the value of dragon.state as '6', Laurena will print "sleepy hungry".

## Defining a bitset field ##

You must first define strings for your bit set using laurena::string\_array class. You can do it this way for example, using a space character as a separator between enum keywords.

```
string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;
```

To declare a field as a bitset, simply use the field::isBitSet(const string\_array&) method once you have initialized your field.

Example:
```
    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->init_field(user,"gender",_gender).isEnum(genders);
    d->init_field(user,"type",_type).isEnum(user_types);
    d->init_field(user,"age",_age);
    d->init_field(user,"name",_name);
```

## Example of serialization and marshalling ##

Let's serialize an user
```
	// let's create our user
	user Paulo;
	Paulo._age = 32;
	Paulo._gender = 0; // male
	Paulo._type = 1; // professor
	Paulo._name = "Paulo" ;

	// let's serialize Paulo !!
	std::string destination = json::json::serialize(Paulo);

	// Let's display my jsoned cat :
	std::cout << "Details of Paulo are :" << std::endl << destination << std::endl;
```

We will get the following output:
```
Details of Paulo are :
{
	"user":
	{

		"gender": "male",
		"type": "professor",
		"age": 32,
		"name": "Paulo"
	}
}
```


Now let's verify gender and type can be marshalled from a string value :
```
	// let's clone Paulo with marshalling
	user PauloCloned;
	json::json::parse(destination,PauloCloned);
	std::cout << "Paulo's clone details are : name=" << PauloCloned._name << ", gender=" << (genders [PauloCloned._gender]) << ", type=" << (user_types[PauloCloned._type]) << ", age=" << ((int) PauloCloned._age) << std::endl;

```

And we get:
```
Paulo's clone details are : name=Paulo, gender=male, type=professor, age=32
```