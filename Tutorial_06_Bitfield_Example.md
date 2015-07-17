Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t06_bitfield_example/main.cpp


## Setting a descriptor for a bit field ##

Let's create a dragon class to describe dragons !

```
//A class with two kind of bitfield
class dragon 
{
public:

	dragon () : _state(0), _name() { _foods.resize(5); };

	unsigned char           _state;	// masks are 1 for 'happy', 2 for 'hungry', 4 for 'sleepy'
	boost::dynamic_bitset<> _foods; // 0 for knight, 1 for princess, 2 for cow, 3 for peasant, 4 for horse
	std::string             _name;
};
```

Laurena supports two kinds of bit fields :

> - The boost class boost::dynamic\_bitset<>. See http://www.boost.org/doc/libs/1_55_0/libs/dynamic_bitset/dynamic_bitset.html. Dynamic bitset are usually used for very large number of bits or for dynamic size of bits.

> - Numeric type (unsigned char, int ...) , like `dragon::_state`' field. Bits are setted and tested using logical operations (AND, OR, ...)

Laurena does have a default class descriptor for boost::dynamic\_bitset<> so there is nothing special to do to serialize a such field.

To register these two fields as bit fields, annotate them with a list of string values. See [Tutorial\_05\_Enum\_Serialization](Tutorial_05_Enum_Serialization.md) for explains about annotations.

Note that we use the **format\_bitset** annotation instead of the **format\_enum** one.

```
string_array dragon_states = "happy hungry sleepy";
string_array dragon_foods  = "knight princess cow peasant horse" ;

void build_dragon_descriptor()
{
    // create class descriptor for the class 'dragon'
	auto d = standard_class_descriptor<dragon>::build("dragon");
	d->add_field(&dragon::_name,"name");
	d->add_field(&dragon::_state,"state").annotate(new format_bitset("format.all", dragon_states));
	d->add_field(&dragon::_foods,"food").annotate(new format_bitset("format.all", dragon_foods));
}
```


## Example of serialization and marshalling ##

Let's serialize a dragon
```
	// let's create our dragon
	dragon smaug;
	smaug._name = "Smaug";
	smaug._state = 3 ; // hungry + happy
	smaug._foods.set(0); // smaug eat knights
	smaug._foods.set(4); // and horses

	// let's serialize smaug !!
	std::string destination = json::json::serialize(smaug);

	// Let's display my jsoned dragon :
	GLOG << "Details of our dragon are :" << std::endl << destination << std::endl;
```

We will get the following output:
```
Details of our dragon are :
{
	"dragon":
	{

		"name": "Smaug",
		"state": "happy hungry",
		"food": "knight horse"
	}
}
```


Now let's verify our bit fields can be marshalled from a string value :
```
	// let's clone smaug with marshalling
	dragon d;
	std::string states, foods;
	json::json::parse(destination,d);

	bitset::serialize((word64)d._state,dragon_states,states,",");
	bitset::serialize(d._foods,dragon_foods,foods,",");
	std::cout << "Cloned dragon details are : name=" << d._name << ", state=(" << states << "), foods=(" << foods << ")" << std::endl;
```

And we get:
```
Cloned dragon details are : name=Smaug, state=(happy,hungry), foods=(knight,horse)
```

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t06_bitfield_example/main.cpp