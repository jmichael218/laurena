# Introduction #

laurena::any is an enhanced version of boost::any. (See http://http://www.boost.org/doc/libs/release/libs/any/)

It is pretty much the same but laurena::any holds the class descriptor of its content and allows so new features by calling methods of the descriptor :

- lexical convert when descriptor support it :
```
    any a = (int) 3;
    std::string s = anycast<std::string>(a); /// will assign "3" to s. Works with laurena, not with boost, thanks to descriptor->toString()
```

- equals operator based on stringified values when possible ( any("3") == any((unsigned char) 3) == any((int) 3) )

- support cast to a parent class