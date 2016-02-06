using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KEYWORD_IN
{
    // Para vc tornar um parameter generico contra-varainte
    // conversao de um tipo generico para um tipo mais especifico)
    // vc deve utilizar a keyword "in", você esta permitindo que o
    // parametro receba um argumento mais generico que o especificado

    //exemplo

    interface IContravariante<in T>
    {
        // ...
    }


    // A interface IContravariante é contravarariante, ou seja
    // vc pode utilizar tipos mais genericos que o especificado pela
    // interface sem metodo de conversao especificos.
    
    // imagine a seguinte classe que implementa esta interface e o restante
    // do código.

    public class TesteContravariance<T> : IContravariante<T>
    {
        // ...
    }

    class Program
    {
        static void Main(string[] args)
        {
            IContravariante<Object> ICovObj = new TesteContravariance<Object>();
            IContravariante<String> iCovStr = new TesteContravariance<String>();


            // nao ocasiona erro: IContravariante é uma interface contravariante
            iCovStr = ICovObj;

        }
    }
}
