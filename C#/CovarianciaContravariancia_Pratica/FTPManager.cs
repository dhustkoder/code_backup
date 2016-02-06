using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CovarianciaContravariancia_Pratica
{
    public class FTPManager<T> : IStorer<T>, IReader<T>
    {
        private List<T> _list = new List<T>();

        public void Store(T item)
        {
            _list.Add(item);
        }

        public T Read(int id)
        {
            return _list[id];
        }
    }
}
