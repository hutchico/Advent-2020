import sys
from functools import reduce

def chinese_remainder(n, a):
    sum = 0
    prod = reduce(lambda a, b: a*b, n)
    for n_i, a_i in zip(n, a):
        p = prod // n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod
 
 
 
def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

with open("input.txt") as file:
    busnums = []
    offsets = []
    incr = 0;
    raw = file.readline()
    raw = file.readline()
    raw = raw.split(',')
    for x in range(len(raw)):
        if(raw[x] != "x"):
            busnums.append(int(raw[x]))
            offsets.append(incr * -1)
        incr += 1

    print(chinese_remainder(busnums,offsets))
