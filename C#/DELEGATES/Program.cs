using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DELEGATES
{
    // delegates are special classes
    // that serve as pointer to methods
    // example
    public delegate int CalcDelegate(int a, int b);

    public static class Test
    {
        public static void Process(CalcDelegate c)
        {
            Console.WriteLine(c(10, 10));
        }
    }

    class CallDelegates
    {
        public void Execute()
        {
            var sum = new CalcDelegate(Sum);
            var sub = new CalcDelegate(Sub);
            var mul = new CalcDelegate(Mul);

            Test.Process(sum);
            Test.Process(sub);
            Test.Process(mul);

            // or
            Console.WriteLine(sum(6, 6) + sub(4, 10) + mul(10, 10));

            // we can also add more func to 1 delegate
            var allCalcs = sum + sub + mul;

            Console.WriteLine(allCalcs(10, 10));
        }


        int x = 10;

        int Sum(int a, int b)
        {
            return x += (a + b);
        }
        int Sub(int a, int b)
        {
            return x += (a - b);
        }
        int Mul(int a, int b)
        {
            return x += (a * b);
        }

    }


    class Program
    {

        static void Main(string[] args)
        {
            CallDelegates x = new CallDelegates();
            x.Execute();
        }
    }
}
