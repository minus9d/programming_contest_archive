
# $ julia d.jl < input_file

function solve()
    K,C,S = map(x -> parse(BigInt,x), (readline() |> split))

    minimum = div(K+C-1, C)
    if S < minimum
        println("IMPOSSIBLE")
        return
    end

    ans = []
    nxt = BigInt(0)
    for m = 0:minimum-1
        idx = BigInt(0)
        for c = C-1:-1:0
            # K ^ c = c-th power of K
            idx += (K ^ c) * nxt
            nxt += 1
            if (nxt == K)
                nxt -= 1
            end
        end
        push!(ans, idx+1)
    end
    println(join(ans, " "))
end

function main()
    T = parse(Int,readline())
    for t = 1:T
        print("Case #$t: ")
        solve()
    end
end

main()
