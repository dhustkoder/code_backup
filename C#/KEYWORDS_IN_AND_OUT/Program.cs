using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KEYWORDS_IN_AND_OUT
{
    class Program
    {
        // Para vc tornar um parâmetro genérico covariante
        // vc deve utilizar a keyword out.
    
        // ao especificar este parametro em uma interface ou delegate.
        // quando vc define um parametro generico com a keyword out
        // vc esta falando que o tipo generico pode ser especificado por um tipo
        // mais especifico que o defino pela interface

        interface ICovariante<out T>
        {
            // neste caso, a interface ICovariante é uma interface covariante,
            // ou seja vc pode utilizar tipos mais genericos no lugar do tipo
            // especificado por T sem nenhum metodo especial para conversao.
        }
        // exemplo

        public class TesteCovariancia<T> : ICovariante<T>
        {

        }

        static void Test()
        {

            ICovariante<object> iCovObj = new TesteCovariancia<object>();
            ICovariante<string> iCovStr = new TesteCovariancia<string>();


            // nao ocasiona erro: ICovariante é uma interface covariante
            iCovObj = iCovStr;

        }

        // A interface ICovariante é uma interface covariante, pois o parametro generico dela
        // foi definido com a palavra out


        // A classe TesteCovariancia implementa a interface ICovariante, portanto
        // objetos do tipo TesteCovariancia<T> também sao objetos
        // covariantes

        // O codigo acima compila sem problemas, ja que os objetos implementam a interface
        // ICovariante (que é covariante), o compilador 
        // consegue converter tranquilamente o objeto ICovStr
        // do tipo (TesteCovariancia<String> - mais especifico)
        // para o tipo
        // Object mais generico

        // se vc nao especificar o parametro generico T da interface
        // utilizando a keyword out, um erro de compilaçao
        // sera gerado ao fazer atribuiçao "IcovObj = ICovStr"
        // pois o compilador nao entendera que deve fazer a conversao
        // do tipo generico de maneira implicita, vc tera uma interface
        // invariante

        static void Main(string[] args)
        {
            // um exemplo classico de uma interface do proprio framework
            // é a interface IEnumerable. se vc reparar na assinatura
            // desta interface, contrara o seguinte codigo
            //   public interface IEnumerable<out T> : IEnumerable { }

            // sendo assim ela é uma interface covariante, entao o seguinte
            // codigo compila sem problemas

            IEnumerable<string> strings = new List<string>();

            IEnumerable<object> objects = strings;

            // como a interface IEnumerable é covariante, a atribuiçao de uma
            // enumeraçao de strings (tipo mais especifico) é feita
            // de maneira implicita para uma outra enumeraçao de objects(mais generico)

        }
    }
}
