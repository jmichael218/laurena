## Welcome ##
Laurena is a non-intrusive LGPL C++11 library implementing basis for serialization of datas. The library offers core classes to handle serialization in data interchange languages like json or xml. It can be used for datas exchanges over the web, to read and parse config files, and in a persistance engine.

Laurena compiles for windows and linux.

Laurena uses features of C++11 like lambda functions and needs Visual Studio 12 or GCC 4.7.

## How works Laurena ? ##
Laurena is based on a set of rich RTTI (real time type infos) classes implemented above the native C++ RTTI. While other serialization libraries like boost::archive are based on archive classes and input/output functions, Laurena uses its RTTI informations to generate output and input in any supported language without the need for the user to write input/output functions to and from an archive class. It allows Laurena to be used beyond simple serialization languages in any other context RTTI is usefull. For example, Laurena support (very basically) the scripting language Velocity.

**Supported languages are :**
  * json
  * xml
  * mdl (my own markup language for data persistance)
  * velocity (output only, see http://velocity.apache.org/)

**Serializables types are :**
  * any atomic type
  * std::string, boost::dynamic\_bitset<>
  * std containers
  * any classes using field members made of supported types.
  * simple heritage of non virtual classes

**Features are :**
  * import/export C++ object to supported markup languages
  * file based persistance for all supported markup languages
  * transparent support of pointer or std::shared\_ptr based field members/container element
  * customization of data format for per class, field and/or language
  * use of Laurena's RTTI informations for script language implementation like Velocity

**Incoming:**
  * sql language
  * xml type injection (like in spring through class="..." attribute)
  * mysql, mariaDB sqlite persistance
  * support of methods for use in script language like velocity
  * virtual classes

## Simple Tutorials ##

Here you will find basic tutorials to learn to use Laurena. Each tutorial is dedicated to one feature of the library.

[Tutorial\_01\_SimpleExample](Tutorial_01_SimpleExample.md) : A first and simple example to show how to serialize a simple class

[Tutorial\_02\_Polymorphic\_Classes](Tutorial_02_Polymorphic_Classes.md) : An example with a parent class and a child class

[Tutorial\_03\_List\_Serialization](Tutorial_03_List_Serialization.md)   : How to build a class descriptor for a list container of a simple class, or of pointer to class objects.

[Tutorial\_04\_Vector\_Serialization](Tutorial_04_Vector_Serialization.md)  : How to build a class descriptor for a vector container.

[Tutorial\_05\_Enum\_Serialization](Tutorial_05_Enum_Serialization.md) : How to declare enum fields, including integer fields with enumerated values.

[Tutorial\_06\_Bitfield\_Example](Tutorial_06_Bitfield_Example.md) : How to declare a bit field or a mask field, including the boost::dynamic\_bitset<> class.

[Tutorial\_07\_Epoch\_Example](Tutorial_07_Epoch_Example.md) : How to declare a field describing a date and time based on an epoch value (seconds since 1970).

[Tutorial\_08\_Custom\_Format\_Example](Tutorial_08_Custom_Format_Example.md) : TODO

[Tutorial\_09\_Persistance\_Example](Tutorial_09_Persistance_Example.md) : How to use a simple json file based persistance to save and read objects.

[Tutorial\_10\_XML\_Example](Tutorial_10_XML_Example.md) : How to serialize and to create object with the XML markup language.

[Toturial\_12\_Serial\_Key\_Example](Toturial_12_Serial_Key_Example.md); In a persistance engine, how to create and use a serial key.

[AGetterAndSetterExample](AGetterAndSetterExample.md) : How to use class methods of kind setters and getters to work around private and protected fields and serialize them.

## Annotations ##

[JsonCustomization](JsonCustomization.md) : How to customize field format in JSON through annotations

## Laurena Classes ##

[AnyClass](AnyClass.md) : An enhanced version of the boost::any class with lexical cast and type info.