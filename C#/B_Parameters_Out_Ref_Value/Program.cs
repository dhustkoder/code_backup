using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_Parameters_Out_Ref_Value
{
    class Program
    {
        // There are three ways that parameters can
        // be passed to a method

        // 1 Value parameters:
        // this method copies the actual value of an
        // argument into the formal parameter of the function.
        // in this case, changes made to the parameter inside the function
        // have no effect on the argument.


        // 2 Reference parameters:
        // this method copies the reference to the memory
        // location of an argument into the formal parameter
        // this means that changes made to the parameter affect the argument

        // 3 Out parameters:
        // this method helps in returning more than one value


        // output parameters are similar to references parameters
        // except that they transfer data out of the method rhater
        // than into it. Reference parameter copies the
        // reference to the memory location of an argument into 
        // the formal parameter. This means that changes made to
        // the parameter effect the argument.

        public static void Test(ref String x, out int y, int byValue)
        {
            y = 10; // must be assgined before leaving function
            x = null; // modifes the original argument x
            byValue = 00;
        }

        static void Main(string[] args)
        {
            String x = "lalla";

            int x1  = 10;
            int x2;
            Test(ref x, out x2, x1);

            if (x == null && x2 == 10 && x1 == 10)
                Console.WriteLine("Yea");
        }
    }
}
