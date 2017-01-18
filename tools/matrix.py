#!/usr/bin/python

import sys
import numpy

if len(sys.argv) < 2:
    print "Missing argument!"
    sys.exit()

size = int(sys.argv[1])
prob = float(sys.argv[2]) if len(sys.argv) > 2 else 0.1
# print size
m = numpy.random.ranf(size=(size,size))

for i in range(0,size):
    for j in range(0,size):
        m[i][j] = 1 if m[i][j] < prob else 0

m[0][0] = 0
for i in range(1,size):
    for j in range(0,i):
        if i == j: continue
        m[j][i] = m[i][j]
    m[i][i] = 0

# Output

for i in range(0,size):
    for j in range(0,size):
        print int(m[i][j]),
    print
