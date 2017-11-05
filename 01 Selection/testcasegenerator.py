import random
import sys
sys.stdout = open("input.txt", "w")
n = int(sys.argv[1])

k = 1

if (n > 1000000):
    k = n/1000000
    n = 1000000

for i in range(k):
    x = random.sample(range(-n/4, n), n)
    for each in x:
        print each
