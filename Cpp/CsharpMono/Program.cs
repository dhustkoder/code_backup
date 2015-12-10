using System.IO;
using System;
using System.Diagnostics;
using System.Reflection;
namespace MonoTest
{

	interface IKey {}

    class Node
    {
        public int value { get; set; }
        private Node next = null, previus = null;
        

		public void setNext<TKey>(Node newNext) where TKey : List, IKey 
		{
			next = newNext;
		}

		public Node getNext<TKey>() where TKey : List, IKey
		{
			return next;
		}

		public void setPrevius<TKey>(Node newPrev) where TKey : List, IKey 
		{
			previus = newPrev;
		}

		public Node getPrevius<TKey>() where TKey : List, IKey
		{
			return previus;
		}
			

        public Node(int x)
		{
			value = x;
		}
    }

    class List
    {


        private Node head = null;
        private Node tail = null;

        public List()
        {

        }


		class ListKey : List, IKey {}

        public void push(int x)
        {
            if (head == null)
            {
                head = tail = new Node(x);
                return;
            }

            var newNode = new Node(x);

			newNode.setNext<ListKey>( head );
			head.setPrevius<ListKey> (newNode);
            head = newNode;
        }


        public void pop()
        {
			head = head.getNext<ListKey>();
			head.setPrevius<ListKey>(null);
        }

        public void listNumbers()
        {
            for (var itr = head; itr != null;)
            {
                Console.WriteLine(itr.value);
				itr = itr.getNext<ListKey>();
            }
        }


    }



    class MainClass
    {

        static void doWork()
        {
            List list = new List();

            for (int i = 0; i < 1000000; i++)
            {
				if (i % 2 == 0) {
					list.push (i);
				}
            }

            list.listNumbers();

        }

        public static void Main(string[] args)
		{
			doWork();

            Console.Read();

            return;
        }
    }


}