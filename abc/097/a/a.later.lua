a, b, c, d = io.read("*n", "*n", "*n", "*n")
if math.abs(a - c) <= d or (math.abs(a - b) <= d and math.abs(c - b) <= d) then
  print("Yes")
else
  print("No")
end
