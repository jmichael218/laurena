## Define customized JSON format for a class ##

Let's say you do have the following vertex and triange classes :
```

class ivertex
{
public:

	ivertex () : _x (0), _y (0) {}
	int _x, _y;
};


class itriangle
{
public:

	itriangle () : _v0 (), _v1 (), _v2 () {}
	ivertex	 _v0, _v1, _v2;
};
```

Instead of printing vertex with x and y values, to have a compact format, we would prefer to use the "(x,y)" format.

We implement the operator >> for the ivertex class + tokenizers, then the operator << for ostreams

**Declarations**
```
std::ostream& operator << (std::ostream& dest, const ivertex& v);
laurena::tokenizer& operator >> (laurena::tokenizer& source, ivertex& v);
```

**Implementations**
```
std::ostream& operator << (std::ostream& dest, const ivertex& v)
{
    return dest << "(" << v._x << "," << v._y << ")" ;
}

tokenizer& operator >> (tokenizer& source, ivertex& v)
{
    return source >> '(' >> v._x >> ',' >> v._y >> ')' ;
}
```

These functions are used by the annotation 'format'.

We are now ready to create the class descriptors and annotate it :

**ivertex class descriptor:**
```
    auto d = standard_class_descriptor<ivertex>::build("ivertex");
    d->init_field(ivertex,"x",_x);
    d->init_field(ivertex,"y",_y);
    d->annotate(new format("json",new generic_writer<ivertex> () , new generic_parser<ivertex> () ));
```

You'll notice the d->annotate (annotation**) call**

**itriangle class descriptor:**
```
    auto d = standard_class_descriptor<itriangle>::build("itriangle");
    d->init_field(itriangle,"v0",_v0);
    d->init_field(itriangle,"v1",_v1);
    d->init_field(itriangle,"v2",_v2);
```

## Tests ##

Let's test the output of a json with a customized format for ivertex instances :
```
    itriangle t;

    t._v0._x = 1;  t._v0._y = 2;
    t._v1._x = 3;  t._v1._y = 4;
    t._v2._x = 5; t._v2._y = 6;

	
    // let's serialize our triangle
    std::string destination = json::json::serialize(t);

    // Let's display my jsoned triangle :
    std::cout << "Our triangle is :" << std::endl << destination << std::endl;
```

We get:
```
Our triangle is :
{
    "itriangle":
    {
        "v0": "(1,2)",
        "v1": "(3,4)",
        "v2": "(5,6)"
    }
}
```

Now let's test the loading of this format :
```
    // let's marshall it in a new triangle
    itriangle t2;
    json::json::parse(destination,t2);
```

And we get:
```
Our new triangle is : v0=(1,2), v1=(3,4), v2=(5,6)
```