using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{
    class Level2 : Level1
    {
        public virtual void Use()
        {
            Console.WriteLine("I'm Level2");
        }
    }
}
