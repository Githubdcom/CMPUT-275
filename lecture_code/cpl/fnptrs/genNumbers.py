import random
import sys

if len(sys.argv) != 2:
  print(f"Usage: {sys.argv[0]} n")
  sys.exit(1)

n = int(sys.argv[1])

for i in range(n):
  print(random.randint(-1*n, n), end=" ")
print()

