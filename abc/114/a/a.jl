
# $ julia a.jl < input_file

function solve()
    X = parse(Int,readline())
    if X == 3 || X == 5 || X == 7
        println("YES")
    else
        println("NO")
    end
end
  
solve()
