using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_REFERENCE_TYPE
{
    class Program
    {
        static void Main(string[] args)
        {
            // The reference types do not contain the actual data
            // stored in a variable, but they contain a reference to
            // the variables.

            // In other words, they refer to a memory location.
            // Using multiple variables,
            // the reference types can refer to a memory location.
            // if the data in the memory location is changed
            // by one of the variables, the other variable
            // automatically reflects this change in value.
            // Example of built-in reference types are:
            // object, dynamic, string


            // Object Type is the ultimate base class for all data types in
            // C# common type System (CTS). Object is an alias for System.Object class
            // the object types can be assigned values of any other type, value types,
            // reference type, predefined or user-defined types. However before assigning
            // values it needs type conversion

            // When a value type is converted to object type, it is called boxing
            // and on the other hand, when an object type is converted to a value type
            // it is called unboxing
            double e = 2.44;
            object obj;
            obj = e; // boxing

            //int ee = (int)obj; // runtime exception

            int ee = (int)(double)obj; // ok
            // first we have to unbox the double
            // and then cast that to an int


            // other thing

            double _x = 2.9;
            double _d = _x; // assign value (not ref)
            object o1 = _d; // boxing, assign ref
            object o2 = _x; // yet other boxing

            Console.WriteLine(_d == _x); // 1
            Console.WriteLine(o1 == o2); // 0


            // thats because the == operator on reference
            // types use reference equality which checks if
            // the references are eqqual, not if the underlying
            // values are equal
            // this is a dangerously easy mistake to make
            // perhaps even more subtle
            Console.WriteLine((double)o1 == (double)o2); // 1
        }
    }
}
