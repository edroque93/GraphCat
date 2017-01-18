#!/usr/bin/python

import sys
import numpy
import argparse

parser = argparse.ArgumentParser(description='Create a random sausage graph.')
parser.add_argument('-n', action='store', default=10, dest='size', type=int, help='size of matrix')
parser.add_argument('-w', action='store', default=4, dest='win', type=int, help='window size')
parser.add_argument('-p', action='store', default=0.4, dest='prob', type=float, help='connection probability')
parser.add_argument('-s', action='store', default=2, dest='step', type=int, help='step size')

args = parser.parse_args(sys.argv[1:])

m = numpy.zeros(shape=(args.size,args.size))

# Init
for w in range(0, args.size-args.win+1, args.step):
    for i in range(w,w+args.win):
        for j in range(w,w+args.win):
            m[i][j] = 1 if numpy.random.ranf() < args.prob else m[i][j]


# Diagonalize
m[0][0] = 0
for i in range(1,args.size):
    for j in range(0,i):
        if i == j: continue
        m[j][i] = m[i][j]
    m[i][i] = 0

# Output
for i in range(0,args.size):
    for j in range(0,args.size):
        print int(m[i][j]),
    print
