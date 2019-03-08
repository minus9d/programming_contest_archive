a, b = io.read(): match("(.+)%s(.+)")
print(string.format("%d", math.max(math.max(a + b, a - b), a * b)))
