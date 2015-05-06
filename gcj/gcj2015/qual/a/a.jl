function solve(smax, shys)
    people = 0
    ret = 0
    for s = 0:smax
        shy_n = int(shys[s+1] - '0')
        #println("s = ", s, ". shy_n = ", shy_n)
        if people < s && shy_n > 0
            ret += (s - people)
            people += (s - people) + shy_n
        else
            people += shy_n
        end
        #println("ret, people = ", ret, ", ", people)
    end
    return ret
end

function readinput()
    smax, shys = readline() |> split
    smax = int(smax)
    return smax, shys
end

function main()
    T = readline() |> int
    for t = 1:T
        println("Case #$t: ", solve(readinput()...))
    end
end

main()
