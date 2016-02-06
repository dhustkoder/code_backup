using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A_JAGGED_ARRAY
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
                C# is a modern, general purpose, object-oriented,
                programming language developed by MS.
                C# is designed for Common Language Infrastructure
                (CLI), Which consist of the executable code and runtime
                environment that allows use of various high-level languages on
                different computer plataforms and architectures
            */

            // Jagged Array:
            // A Jagged array is an array of arrays.

            // You can initialize a jagged array as −
            int[][] arrOfArr = new int[2][]{new int[] { 10, 20, 30 }, new int[] { 10,30,40, 60} };
            //Where, 
            //arrOfArr is an array of two arrays of integers -
            //arrOfArr[0] is an array of 3 integers 
            //arrOfArr[1] is an array of 4 integers.


            foreach (int[] arr in arrOfArr)
            {
                foreach (int n in arr)
                    Console.WriteLine(n);
            }



        }
    }
}
