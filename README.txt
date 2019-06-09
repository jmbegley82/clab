No-name collection of multi-purpose objects

All objects (except Atom) are derived from Atom.


Basic Types:
============
Atom   - one does not typically use this class directly, but it is useful to
           cast derived classes as Atoms to pass them around
Node   - Atoms which store other Atoms; can be nested to create hierarchical
           object trees
Notype - this internal-use-only Atom is created in error conditions; when an
           Atom attempts to Dereference another Atom that isn't accessible to
           it, a Notype is created whose Identity (and only relevant data) is
           the text string of the inaccessible Atom.  Notypes are also created
           when a Atom can't be _Interpreted due to eg. incompatibility. 


Standard Data Types:
====================
Integer- Stores a signed integer (range is determined by compiler)
Float  - Stores a signed floating-point number (range determined by compiler;
           data type used is 'double')
String - Stores a c++ std::string (specifics determined by compiler)

All standard data types can _Interpret each other.  Floats _Interpreted as
Strings are currently in the format of %16.16f.  Floats _Interpreted as
Integers are rounded.  If a String is _Interpreted as an Integer or Float and
contains non-numeric data (eg. data not correctly understood by the CRT's
strtod() function), it will be zero.

Tick() and wasUpdated:
======================
All Atoms implement void Tick(int ms), though won't necessarily do anything
with them.  An Atom will call Tick(ms) for every Atom it contains (static or
dynamic as in Node, Video etc.)  Time is currently specified to be in milli-
seconds but may change in the future.
During Tick, an Atom may need to determine whether or not any Atom contained
within has changed since its last Tick.  If the contained Atom has changed, its
wasUpdated flag will be set.  The containing Atom will perform its specified
task and set the contained Atom's wasUpdated flag to false.
Almost none of this functionality has beeen written yet.  Implementations of
Tick should ensure that wasUpdated flags are dealt with correctly; depending
upon context, it may make more sense to set wasUpdated to false as each Atom is
examined, or it may make more sense to Tick all contained Atoms before setting
their wasUpdated flags to false.

Literals:
=========
Variables can be set with Literal values, eg. "Integer i1 = 7".  String
literals must be encapsulated within quotation marks.


Syntax:
=======
[[Declarator] <Subject Atom>] [Assignment Operator <Target>]

An empty string calls the _Procedure of the Atom to which it is issued.  If
a Subject Atom is specified without an operator, its _Procedure is called.  If
a Declarator is specified, the Subject Atom is created of the type specified
by the Declarator.  If an Assignment Operator is specified, a Target (either a
Literal or Atom) must also be specified.

Assignment Operators are =, +=, -=, *=, /=, ^=
Command Operator is :=

Examples:

Create an Integer named i1:
$ Integer i1

Create an Integer named i1 and set it to 7:
$ Integer i1 = 7

Create a String that contains the value of i1:
$ String s1 = i1

Create a String and set its text to "3.14159":
$ String s1 = "3.14159"

Create a Float and set its value to the number contained in s1:
$ Float f1 = s1

Clear a string:
$ s1 := clear

Round a Float:
$ f1 := round

Invert a Float (x = 1/x):
$ f1 := inverse

