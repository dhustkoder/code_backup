using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ARRAYS_COVARIANCE_PROBLEBLA_TIPAGEM
{
    // C# possui há algum tempo o recurso de covariance em arrays
    // Porém este recurso pode pregar uma peça com relação à definição
    // de tipos em arrays, em grande parte por causa do fato de arrays
    // serem elementos reference-type

    public abstract class Pessoa
    {
        // ....
    }


    public sealed class PessoaFisica : Pessoa
    {

    }


    public sealed class PessoaJuridica : Pessoa
    {

    }

    // temos as 3 classes, classe abstrata(pessoa), e as classes concretas (pessoa fisica)
    // (pessoa juridica), ambas derivadas de Pessoa

    


    class Program
    {
        static void Main(string[] args)
        {

            PessoaFisica[] pessoasFisicas = new PessoaFisica[10];

            // covaricância: tipo mais especifico (PessoaFisica) para tipo genérico (Pessoa)
            Pessoa[] pessoas = pessoasFisicas;


            pessoas[0] = new PessoaFisica();
            pessoas[1] = new PessoaJuridica();

            // Código compila pelo fato de que PessoaFisica herda da 
            // classe pessoa, sendo assim , se criarmos um array e definilo
            // como sendo do tipo PessoaFisica, posso atribuir este array para outro tipo Pessoa.
            // como ocorre acima entre os arrays pessoasFisicas e pessoas

            // Note que aqui ocorre uma covariancia: o tipo mais especifico (array de PessoasFisica)
            // é convertido de maneira implicita para um tipo
            // generico (tipo Pessoa). 

            // Porém arrays são reference-type! Se é tanto a variável pessoasFisicas quanto a variavel
            // pessoas estao apontando na verdade para o mesmo espaço de memória na area Heap
            // Seondo assim, quando você adiciona um elemento ao array pessoas, vc tbm esta adicionando um
            // elemento ao array pessoasFisicas, ja que ambos apontam para o mesmo local na memória


            // entao por isso o codigo compila sem problemas mas avera um erro na execuçao
            // ArrayTypeMismatchException, ao tentar adicionar um novo objeto do tipo PessoaJuridica


            // Esta exception é jogada justiamente pela covariancia aplicada de maneira errada

            // Lembre-se:
            // Arrays em C# sao reference-type
            // Temos uma instancia de um array do tipo PessoaFisica: o array "pessoasFisicas"
            // atribuimos a um array do tipo Pessoa o proprio array "pessoasFisicas"
            // e os dois apontam para o mesmo espaço de memoria (address)

            // inicialmente temos nosso array pessoasFisicas, alocadando um
            // espaço de memoria para 10 objetos PessoaFisica
            PessoaFisica[] _pessoasFisicas = new PessoaFisica[10];


            // logo em seguida, atribuimos um array do tipo Pessoa o array do tipo PessoaFisica,
            // sendo dois tipos reference-type, ambos apontam para mesma area na memoria,
            // utilizando Covariancia, um polimorfismo.

            Pessoa[] _pessoas = _pessoasFisicas;


            // logo após utilizamos o array do tipo Pessoa adicionando elementos a ele
            // (lembre-se de que ele esta apontando para o mesmo lugar do tipo PessoaFisica)
            // se adicionarmos um objeto do tipo PessoaFisica, o codigo é executado normalmente,
            // pois PessoaFisica herda de Pessoa e, segundo um principio chamado
            // principio da Substituiçao de Liskov. um array do tipo Pessoa, pode conter
            // objestos do tipo PessoaFisica

            _pessoas[0] = new PessoaFisica();


            // mas logo apos adicionamos um objeto do tipo PessoaJuridica,
            // O compilador nao encontra problemas, pois PessoaJuridica também herda
            // de Pessoa. portanto um array do tipo Pessoa, pode conter elementos do tipo PessoaJuridica
            // mas anteriormente aplicamos no array do tipo Pessoa a covariancia, pois ele esta apontando
            // para a mesma posiçao do array do tipo PessoaFisica.
            // Sendo Assim na verdade, não poderiamos adicionar elementos do tipo PessoaJuridica

            // Por parte do compilador, ele tambem vai aplicar a covariancia para converter
            // o objeto do tipo PessoaJuridica para coloca-lo dentro do
            // array do tipo Pessoa, Porém, em tempo de execuçao, isso causa um erro
            // sério de tipagem,
            // pois na verdade estamos manipulando um array de PessoaFisica também
            // ja que ambos apontam para o mesmo lugar. Assim , o compilador compilando
            // corretamente o codigo, ha uma inconsistencia com relaçao aos tipos
            // que o compilador nao consegue enxergar:
            // um array do tipo Pessoa deve aceitar objetos do tipo PessoaJuridica
            // mas devido ao equivoco da aplicaçao da covariancia, um erro q so pode
            // ser percebido em tempo de execuçao é gerado,
            // ou seja
            // Cuidado ao usar um array covariante!

            //esse problema com a covariancia existe desde quando os arrays passaram a suportar
            // covariancia no C#.
            // esse tipo de problema nao ocorre com estruturas que utilizam generics para 
            // especificar a tipagem.
            // como por exemplo Listas

            List<PessoaFisica> __pessoasFisicas = new List<PessoaFisica>();
            List<Pessoa> pessoas = pessoasFisicas; // erro compilaçao


        }
    }
}
