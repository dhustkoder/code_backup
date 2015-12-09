using System;

namespace MonoTest
{
    class Node
    {
        public int value { get; set; }
        Node _next = null, _previus = null;
        public Node next    { get {return _next; } set {_next = value; } }
        public Node previus { get { return _previus; } set { _previus = value; } }
        public Node(int x)
        {
            value = x;
        }

        ~Node()
        {
            Console.WriteLine("erased node of value " + value);
        }
    }

    class List
    {


        private Node head = null;
        private Node tail = null;

        public List()
        {

        }

        public void push(int x)
        {
            if (head == null)
            {
                head = tail = new Node(x);
                return;
            }

            var newNode = new Node(x);

            newNode.next = head;
            head.previus = newNode;
            head = newNode;
        }


        public void pop()
        {
            head = head.next;
            head.previus = null;
        }

        public void listNumbers()
        {
            for (var itr = head; itr != null;)
            {
                Console.WriteLine(itr.value);
                itr = itr.next;
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
                list.push(i);
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