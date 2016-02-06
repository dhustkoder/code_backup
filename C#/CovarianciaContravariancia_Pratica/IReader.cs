using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{
    interface IReader<out T>
    {
        T Read(int id);
    }
}
