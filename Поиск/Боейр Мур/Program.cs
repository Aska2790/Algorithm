using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Labarator_4_1
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {

                    string[] readText = File.ReadAllLines(@"E:\file.txt");
                    string text = String.Join(" ", readText);
                    string findWord = Console.ReadLine();

                    BoyerMoore bm = new BoyerMoore(findWord);
                    foreach (int index in bm.BoyerMooreMatch(text))
                        Console.WriteLine("Matched at index {0}", index);
             }
            catch { }

            Console.ReadKey();
        }

      

    }
}

