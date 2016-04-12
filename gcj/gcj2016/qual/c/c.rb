#!/usr/bin/env ruby

def solve()
  n,j = gets.split.map {|s| s.to_i}

  numstr = "1" + "0" * (n-1)
  num = numstr.to_i(base=2)

  found = 0
  loop do
    num += 1

    binstr = num.to_s(2)
    if binstr[-1] == '0' then
        next
    end

    ok = true
    divisors = []
    (2..10).each{|base|
      val = binstr.to_i(base)
      cands = [2,3,5,7,11]
      cands.each{|c|
        if val % c == 0 then
          divisors.push(c)
          break
        end
      }
    }

    if divisors.size == 9 then
      print(([binstr]+divisors).join(" "), "\n")
      found += 1
      if found == j then
        break
      end
    end
  end
end
              
  
def main()
    testnum = gets.to_i
    testnum.times do |t|
        puts "Case ##{t+1}:"
        solve()
    end
end

main()
