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


Literals:
=========
Currnetly, literals (at least ones that aren't also names of Atoms accessible
to the Atom in question) become Notypes whose Identities contain the text of
the literal, which are then promptly discarded as there is currently no code
to discern a useful literal from garbage text.  Encapsulating literals eg. in
quotes is one potential solution.


Syntax:
=======
<Atom><Assignment Operator><Atom>
Assume our Node 'root' contains two Integers with Identities 'i1' and 'i2'.
Calling root.Command("i1=i2"); will cause the value of i1 to be set to the
current value of i2.

Assignment Operators are =, +=, -=, *=, /=, ^=


Proposed Syntax:
================
<Atom><Assignment Operator><Literal or Atom>[Operator][Literal or Atom][...]
None of this is currently in place and to incorporate order of operations and
parentheses of any depth will be a major undertaking.

