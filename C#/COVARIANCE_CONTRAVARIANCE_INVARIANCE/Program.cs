using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace COVARIANCE_CONTRAVARIANCE_INVARIANCE
{
    class Program
    {
        static void Main(string[] args)
        {
            string a = "Teste"; // variável
            
            
            //covariância: tipo específico (string) convertido para um genérico (object)
            object obj1 = a;
            
            
            //contravariância: tipo genérico (object) convertido para um específico (string)
            string b = obj1 as string;
            
            
            //invariância: não há conversão de tipos
            String c = b;

        }
    }
}
