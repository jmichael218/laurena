Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t05_enum_example/main.cpp

## Setting a descriptor for an enum field ##
```

enum gender : unsigned char
{
    UNDEFINED,
    MALE,
    FEMALE
};

class user
{
public:
	
    gender          _gender; // a true enum
    unsigned int    _type;   // 0 for student, 1 for professor, 2 for visitor
    unsigned int    _age;
    std::string	    _name;

};
```


Laurena supports two kinds of enums :

> - The real enum type, like the 'gender' type above.
> - A numeric type (unsigned char, int ...) which can have only a small set of values, like the class member `user::_type`.

Laurena does have a mecanism for the two options but both need to declare the string values of each values, using the **laurena::string\_array** class.
string\_array is basically an enhanced std::vector<std::string>.

See https://code.google.com/p/laurena/source/browse/laurena/src/laurena/types/string_array.hpp for more details on this class.

```
string_array genders = "undefined male female" ;
string_array user_types = "student professor visitor" ;
```

Let's set up a class descriptor for the user class:
```
void build_user_descriptor()
{
    auto denum = enum_type_descriptor<gender>::build("gender", genders);

    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->add_field(&user::_gender,"gender");
    d->add_field(&user::_type,"type").annotate(new format_enum("format.all",user_types));
    d->add_field(&user::_age,"age");
    d->add_field(&user::_name,"name");
}
```

As you can see, we create a full class descriptor when a real enum type is used, and we use a new feature called annotation when we want to give string values to a numeric field.

Annotations is like a plugin to a field or a class descriptor, to change a behavior. There is several annotations in the core laurena librarie. Format annotations change the way a field or a class is serialized. format\_enum allow to serialize a numeric value as a string value, as you will see in the following example.


## Example of serialization and marshalling ##

Let's serialize an user
```
    // let's create our user
    user Paulo;
    Paulo._age = 32;
    Paulo._gender = MALE; // male
    Paulo._type = 1; // professor
    Paulo._name = "Paulo" ;

    // let's serialize Paulo !!
    std::string destination = json::json::serialize(Paulo);

    // Let's display my jsoned Paulo :
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

    std::cout<< "Paulo's clone details are : name=" << PauloCloned._name 
         << ", gender=" << (genders [PauloCloned._gender]) 
         << ", type=" << (user_types[PauloCloned._type]) 
         << ", age=" << ((int) PauloCloned._age) 
         << std::endl;

```

And we get:
```
Paulo's clone details are : name=Paulo, gender=male, type=professor, age=32
```

Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t05_enum_example/main.cpp