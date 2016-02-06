using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{
    class Level3 : Level2
    {
        public override void Use()
        {
            Console.WriteLine("I'm Level3");
        }
        public void Level3ExclusiveMethod()
        {
            Console.WriteLine("HeeeyHooo");
        }
    }
}
