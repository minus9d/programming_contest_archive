% octave

line = fgetl(stdin);
testnum = sscanf(line,'%d');

for i = 1:testnum
    printf("Case #%d:\n", i)

    line = fgetl(stdin);
    [NJ,count] = sscanf(line,'%d %d');
    N = NJ(1);
    J = NJ(2);

    numstr = "1";
    for j = 1:N-1
        numstr = strcat(numstr, "0");
    endfor

    found = 0;
    num = int64(bin2dec(numstr));
    while (true)
        num += 1;
        binstr = dec2bin(num);

        if substr(binstr, -1) == '0'
            continue
        endif

        ok = true;
        divisors = {};
        for base = 2:10
            val = base2dec(binstr, base);
            cands = [2 3 5 7 11];

             for c = cands
                if mod(val,c) == 0
%                   printf("%d is dividable by %d\n", val, c);
                   divisors = [divisors, c];
                   break
                endif
            endfor
        endfor

%        printf("mod size:%d\n", size(mod))

        
        if length(divisors) == 9
           found += 1;
           printf("%s", binstr)
           for d = divisors
               printf(" %d", d{1})
           endfor
           printf("\n")

        endif

        if found == J
           break
        endif

    endwhile
end


