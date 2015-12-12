using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication3
{
    interface IWeapon
    {
        int attack();
    }

    interface IConsumable
    {
        int consume();
    }

    class Item
    {
        public Item(String name)
        {
            m_name = name;
        }

        unsafe ~Item ()
        {
            m_name = null;
            
        }

        protected String m_name;
    }


    class Sword : Item, IWeapon
    {
        public Sword(String name) : base(name)
        {

        }

        public int attack()
        {
            return 1;
        }

        ~Sword()
        {
            m_name = null;
        }

        
    }


    class Axe : Item, IWeapon
    {
        public Axe(String name) : base(name)
        {

        }

        public int attack()
        {
            return 2;
        }

        ~Axe()
        {
            m_name = null;
        }
    }


    
    class HealthPotion : Item, IConsumable
    {
        public HealthPotion(String name) : base(name)
        {

        }

        public int consume()
        {
            return 1;
        }

        ~HealthPotion()
        {
            m_name = null;
        }
    }


    class ManaPotion : Item, IConsumable
    {
        public ManaPotion(String name) : base(name)
        {

        }

        public int consume()
        {
            return 2;
        }

        ~ManaPotion()
        {
            m_name = null;
        }
    }



    class Program
    {

        static void useAllItems(System.Collections.Generic.List<Item> itemList)
        {
            var swords = 0d;
            var axes = 0d;
            var healthPotions = 0d;
            var manaPotions = 0d;

            IConsumable consumable;
            IWeapon weapon;

            foreach(Item someItem in itemList)
            {
                if ((weapon = someItem as IWeapon) != null)
                {
                    if (weapon.attack() == 1)
                        ++swords;
                    else
                        ++axes;
                }

                else if ((consumable = someItem as IConsumable) != null)
                {
                    if (consumable.consume() == 1)
                        ++healthPotions;
                    else
                        ++manaPotions;
                }


            }

            Console.WriteLine("Swords in list: " + swords);
            Console.WriteLine("Axes in list: " + axes);
            Console.WriteLine("HealthPotions in list: " + healthPotions);
            Console.WriteLine("ManaPotions in list: " + manaPotions);
            


        }

        static void Main(string[] args)
        {
            const int maxItems = 1000000;
            const int maxLoopTest = 1000;
            var itemList = new System.Collections.Generic.List<Item>();

            for (int X = 0; X < maxLoopTest; ++X)
            {
                for (int i = 0; i < maxItems / 2; ++i)
                {
                    if (i % 2 == 0)
                        itemList.Add(new Sword("Excalibur"));
                    else
                        itemList.Add(new Axe("Horned Axe"));
                }

                for (int i = 0; i < maxItems / 2; ++i)
                {
                    if (i % 2 == 0)
                        itemList.Add(new HealthPotion("Elixir"));
                    else
                        itemList.Add(new ManaPotion("Ether"));
                }
                useAllItems(itemList);
                itemList.Clear();
            }
        }
    }
}
