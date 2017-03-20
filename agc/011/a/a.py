N, C, K = map(int, input().split())
Ts = []
for n in range(N):
	Ts.append(int(input()))
Ts.sort()

bus = 0
bus_t = None
bus_on_board = 0

for t in Ts:
	if bus_t is not None and t <= bus_t and bus_on_board < C:
		bus_on_board += 1
	else:
		bus += 1
		bus_t = t + K
		bus_on_board = 1
print(bus)
