import random
import sys

if len(sys.argv) != 2:
  print(f"Usage: {sys.argv[0]} numOfNums")
  sys.exit(1)

n = int(sys.argv[1])
for i in range(n):
  print(random.randint(-n, n))
