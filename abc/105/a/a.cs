using System;
using System.Linq;
 
public class Program
{
    public static void Main()
    {
        var NK = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
        var N = NK[0];
        var K = NK[1];
        Console.WriteLine(1 * (N % K > 0));
    }
}