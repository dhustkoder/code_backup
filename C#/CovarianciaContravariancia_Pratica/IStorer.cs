using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{
    // interface contravariate
    interface IStorer<in T>
    {
        void Store(T item);
    }
}
