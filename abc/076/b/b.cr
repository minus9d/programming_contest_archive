n = gets.not_nil!.to_i
k = gets.not_nil!.to_i

ans = 1
1.upto(n) do |a|
  ans = {ans + k, ans * 2}.min
end

puts ans
