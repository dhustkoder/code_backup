using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{


    class Program
    {
        static void Main(string[] args)
        {
            var ftp = new FTPManager<Level2>();
            ftp.Store(new Level2());
            ftp.Store(new Level3());

            // have a storer only for Level3s..
            // IStorer is Contravariant
            // which means it can receive
            // a more generic Type T (Level2)
            // and implicit convert to a more
            // specific type T (Level3)
            IStorer<Level3> lvl3Storer = ftp;

            // have a reader for all levels...
            // IReader is co-variant which means
            // that it can receive a specific type T
            // and implicit convert to a more generic type T
            IReader<Level1> lvl1Reader = ftp;


            // using interfaces correctly 
            // using <out T> or <in T>

            // helps us not making mistakes
            // IReader only reads so it can
            // get types of the most generic root of T


            // but IStorer pushes things in
            // so it can't be a type more generic than
            // what ftp variable was created with.


            Console.WriteLine(ftp.Read(0));
            Console.WriteLine(ftp.Read(1));
        }
    }
}
