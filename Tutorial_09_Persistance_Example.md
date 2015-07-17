Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t09_file_persistance_example/main.cpp

## Introduction ##

Persistance is handled by Laurena through a simple class named 'persistance'.

To handle the persistance for each classes, there is also a family of classes called dao (for Direct Access Object) losely based on the dao pattern used in java.

DAOs classes do have the responsability to implement reading and writing functions for a given class.

We do have two kind of DAOs : file based DAOs using a file format like json or xml, and database based DAOs using the sql langage and a connection to a database.

In this example we'll use a json file based persistance.


## Class definition ##
We'll use the same user class from the enum example. There is no prerequisite so a class is persistant or not:

```
// Let's reuse our user class from the enum example
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

## Building the class descriptor ##

The only difference with the enum example is that we define the name field as a primaryKey.

Primary keys are values supposed to be unique for a configured dao.

```
string_array genders    = "undefined male female" ;
string_array user_types = "student professor visitor" ;

descriptor* build_user_descriptor()
{
    auto denum = enum_type_descriptor<gender>::build("gender", genders);

    // create class descriptor for the class 'user'
    auto d = standard_class_descriptor<user>::build("user");
    d->add_field(&user::_gender,"gender");
    d->add_field(&user::_type,"type").annotate(new format_enum("format.all",user_types));
    d->add_field(&user::_age,"age");
    d->add_field(&user::_name,"name");

    //Let"s declare name as the primary field.
    d->primary_key("name");
    return d;
}
```

## Persistance ##

In this example, we have defined a global variable for the persistance engine.
```
persistance DISK;
```

You can have more than one persistance engine also, and each dao can use its own format.

It means inside a same persistance engine, you can save users in json format, accounts in a sql database, and another data as xml files.

You can also save a same class using different daos. Daos are registered in the persistance engine with a 'pipeline' keyword.

```
    // user persistance initialization
    DISK.add("user", std::make_shared<json::json_dao>(*userDescriptor, "datas/users"));
```

This code means we create a json file based dao for the user's class descriptor in the "datas" directory, and that we associate this dao to the pipeline keyword 'user'.

By the way, directories are created when needed


Let's build up our user and save it in the persistance engine:
```
    // let's create a user
    user bob;
    bob._age = 25;
    bob._gender = MALE;
    bob._name = "Bob Joe";
    bob._type = 1; // professor

    // let's save it on disk using the "user" pipeline
    DISK.insert("user", bob);
```

The datas/users/B/Bob Joe.json file is created and has the following content:
```
{
	"user":
	{

		"gender": "male",
		"type": "professor",
		"age": "25",
		"name": "Bob Joe"
	}
}
```

Now let's read Bob's details from the disk:

```
    // let's test the read function
    user bobcloned;
    DISK.select("user", "Bob Joe", &bobcloned);

    // Let's serialize it into json
    std::string destination = json::json::serialize(bobcloned);

    // Let's check create + read worked :
    std::cout << "Here is Bob's details:" << std::endl << destination << std::endl;
```

And we get the following output to confirm Laurena's persistance :
```
Here is Bob's details:
{
	"user":
	{

		"gender": "male",
		"type": "professor",
		"age": "25",
		"name": "Bob Joe"
	}
}
```
Link to full source code : http://code.google.com/p/laurena/source/browse/tutorials/t09_file_persistance_example/main.cpp