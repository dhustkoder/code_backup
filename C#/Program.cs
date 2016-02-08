using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace STUDY
{
    class Circle
    {
        private double radius = 10;
        public Circle(double x)
        {
            radius = x;
        }
        public double calculate(Func<double,  double> f)
        {
            return f(radius);
        }
    }
    class Circle2 : Circle { public Circle2() : base(10) { } }

    interface covariance<out X>
    {
        X getx();
    }

    interface contravariance<in Y>
    {
        void setx(Y y);
    }

    class Cov<X> : covariance<X>, contravariance<X>
    {
        public X getx()
        {
            return Activator.CreateInstance<X>();
        }

        public void setx(X y)
        {
            throw new NotImplementedException();
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            
            var c = new Cov<Circle>();
            covariance<object> x = c;
            contravariance<Circle2> x2 = c;
        }
    }
}
