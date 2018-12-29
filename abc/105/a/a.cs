using System;
using System.Linq;
 
public class Program
{
    public static void Main()
    {
        var NK = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
        var N = NK[0];
        var K = NK[1];
        if (N % K == 0) {
            Console.WriteLine(0);
        } else {
            Console.WriteLine(1);
        }
    }
}