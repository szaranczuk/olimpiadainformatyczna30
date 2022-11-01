from math import log, gcd
n = 1000
lcm = int(1)

for i in range(2, n):
	lcm = i * lcm // gcd(i, int(lcm))
print(log(lcm, 2))
