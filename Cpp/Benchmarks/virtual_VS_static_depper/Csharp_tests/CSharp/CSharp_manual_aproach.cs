using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication3
{


    class Item
    {


        public enum ItemType
        {
            Weapon,
            Consumable
        }

        public Item(String name, ItemType type)
        {

            m_name = name;
            m_type = type;
        }

        public ItemType getType()
        {
            return m_type;
        }

        unsafe ~Item()
        {
            m_name = null;

        }

        protected String m_name;
        private ItemType m_type;

    }


    class Weapon : Item
    {
        public enum WeaponType
        {
            Sword,
            Axe
        }

        public Weapon(String name, WeaponType type) : base(name, ItemType.Weapon)
        {
            m_weaponType = type;
        }

        public int attack()
        {
            if (m_weaponType == WeaponType.Sword)
                return ((Sword)this).attack();
            else if (m_weaponType == WeaponType.Axe)
                return ((Axe)this).attack();

            return 0;
        }

        private WeaponType m_weaponType;
    }



    class Sword : Weapon
    {
        public Sword(String name) : base(name, WeaponType.Sword)
        {

        }

        public new int attack()
        {
            return 1;
        }

        ~Sword()
        {
            m_name = null;
        }

    }


    class Axe : Weapon
    {
        public Axe(String name) : base(name, WeaponType.Axe)
        {

        }

        public new int attack()
        {
            return 2;
        }

        ~Axe()
        {
            m_name = null;
        }
    }

    class Consumable : Item
    {

        public enum ConsumableType
        {
            HealthPotion,
            ManaPotion
        }

        public Consumable(String name, ConsumableType type) : base(name, ItemType.Consumable)
        {
            m_consumableType = type;
        }

        public int consume()
        {
            if (m_consumableType == ConsumableType.HealthPotion)
                ((HealthPotion)this).consume();
            else if (m_consumableType == ConsumableType.ManaPotion)
                ((ManaPotion)this).consume();



            return 0;
        }

        private ConsumableType m_consumableType;
    }


    class HealthPotion : Consumable
    {
        public HealthPotion(String name) : base(name, ConsumableType.HealthPotion)
        {

        }

        public new int consume()
        {
            return 1;
        }

        ~HealthPotion()
        {
            m_name = null;
        }
    }


    class ManaPotion : Consumable
    {
        public ManaPotion(String name) : base(name, ConsumableType.ManaPotion)
        {

        }

        public new int consume()
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


            foreach (Item someItem in itemList)
            {
                if (someItem.getType() == Item.ItemType.Weapon)
                {
                    if (((Weapon)someItem).attack() == 1)
                        ++swords;
                    else
                        ++axes;
                }
                else if (someItem.getType() == Item.ItemType.Consumable)
                {
                    if (((Consumable)someItem).consume() == 1)
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
            itemList.Capacity = maxLoopTest;

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

