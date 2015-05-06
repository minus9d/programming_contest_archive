function solve()
    local line = io.read()

    -- split into two string
    local words = {}
    for s in string.gmatch(line, '%S+') do
        table.insert(words, s)
    end

    local smax = tonumber(words[1])
    local shys = words[2]

    local people = 0
    local ret = 0
    for s = 0, smax do
        local shy_n = tonumber( shys:sub(s+1,s+1) )
        if (people < s and shy_n > 0) then
            ret = ret + (s - people)
            people = people + (s - people) + shy_n
        else
            people = people + shy_n
        end
    end
    return ret
end

function main()
    local ntest = tonumber(io.read())
    for i = 1, ntest do
        print("Case #" .. i .. ": " .. solve())
    end
end

main()
