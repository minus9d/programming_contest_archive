#!/bin/env ruby

# ñ‚ëË 
# éQçl http://code.google.com/codejam/contest/dashboard?c=188266#s=a&a=2

def combination(n, r)
	ret = 1
	for i in 0..(r-1)
		ret *= (n - i)
	end
	for i in 0..(r-1)
		ret /= (i + 1)
	end
	return ret
end

def possibilityOfYDCardsWhenXCards(x, y)
	val1 = combination(C-x, y-x)
	val2 = combination(x, N-(y-x))
	val3 = C_CHOOSE_N
	return 1.0 * val1 * val2 / val3
end

C = 1000000
N = 15
C_CHOOSE_N = combination(C, N);


Es = Array.new(C + 1)
Es[C] = 0.0
(C-1).downto(0) { |i|

	puts "i = " + i.to_s() if i % 100 == 0

	yMax = C < i+N ? C : i+N
	temp = 1.0;
	for y in i+1..yMax
		temp += possibilityOfYDCardsWhenXCards(i, y) * Es[y]
	end

	Es[i] = temp / (1.0 - possibilityOfYDCardsWhenXCards(i, i));
}

puts Es[0]

#answer = 959508.864903438

