using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace D_MORE_ON_REFERENCE_VS_VALUE_TYPES
{
    // one thing to note
    struct SPoint
    {
        public int x, y;
    }

    class CPoint
    {
        public int x, y;
        
    }


    class Program
    {
        static void Main(string[] args)
        {

            CPoint classPoint = new CPoint();
            classPoint.x = 100;
            classPoint.y = 100;


            SPoint structPoint = new SPoint();
            structPoint.x = 100;
            structPoint.y = 100;

            object asbtract = classPoint; // reference
            object asbtract2 = structPoint; // value

            classPoint.x = 0;
            structPoint.x = 0;

            Console.WriteLine("class : " + ((CPoint)asbtract).x); // 0
            Console.WriteLine("struct : " + ((SPoint)asbtract2).x); // 100

            // for value types:
            // A boxing conversion makes a copy of the value being boxed
            // explainig the diference in bahaviour




            // DEEP:
            // The types in .NET framework are either treated by Value Type
            // or Reference Type. 
            // -- A value Type holds the data within Its own memory allocation, 

            // -- and a Reference type contains a pointer to another memory location
            // that holds the real data.

            // Reference Type variables goes in the Heap, 
            // while Value type variables are stored in the stack.



            // VALUE_TYPE:
            // A value type stores its contents in memory
            // allocated on the stack.

            // when u create a value type, a single
            // space in memory is allocated to store the value
            // and that variable directly holds a value.

            // If you assign it to another variable, the
            // value is copied directly and both variables
            // work independently.
            // Predefined datatypes,
            // structures, enums are also value types,
            // and work in the same way.
            // Value types can be created at compile time
            // and Stored in stack memory.
            int i = 0;
            int x = i; // copy i's value into x;

            // REFERENCE_TYPE:
            // reference types are used by a reference which holds a reference
            // (address) to the object but not the object itself.

            // Because reference types represent the address of the variable rather than the data
            // assigning a reference variable to another doesn't copy
            // the data. Instead it created a second copy of the reference, which
            // refers to the same location of the head, as the original value.
            // Reference types variables are stored in a different area of memory
            // called heap. This means that when a reference type variable is no longer
            // used, it can be marked for garbage collection. examples of reference types
            // are Classes, Objects, Arrays, Indexers, Inderfaces, Etc.

            CPoint p1 = new CPoint();
            CPoint p2 = p1;

            p1.x = 200;
            Console.WriteLine(p2.x);
        }
    }
}
