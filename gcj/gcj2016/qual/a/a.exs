defmodule Main do
  def main do
    tt = IO.gets("")
    {tt, _} = Integer.parse(tt)
    for t <- 1..tt do
      n = IO.gets("")
      {n, _} = Integer.parse(n)
      IO.puts "Case ##{t}: #{solve(n)}"
    end
  end

  def solve(n) do
    if n == 0 do
      :INSOMNIA
    else
      seen = MapSet.new([])
      ans = func(n, 1, seen)
    end
  end

  def func(n, cnt, seen) do
    if MapSet.size(seen) == 10 do
      (cnt-1)*n
    else
      tmp = Integer.digits(n*cnt)
      tmp = MapSet.new(tmp)
      seen = MapSet.union(seen,tmp)
      func(n, cnt+1, seen)
    end    
  end
end

Main.main

