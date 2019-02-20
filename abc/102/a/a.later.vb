module ABC102A
  sub Main(ByVal args() as String)
    dim n as integer
    n=Console.ReadLine()
    if n Mod 2 = 0
      Console.WriteLine(n)
    else
      Console.WriteLine(n * 2)
    end if
  end sub
end module
