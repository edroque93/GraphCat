#!/usr/bin/python

import sys
import numpy
import argparse

parser = argparse.ArgumentParser(description='Create a random tree graph.')
parser.add_argument('-n', action='store', default=10, dest='size', type=int, help='size of matrix')
parser.add_argument('-k', action='store', default=0.8, dest='connect', type=float, help='connectitivty factor')

args = parser.parse_args(sys.argv[1:])

def genline(m,n,p):
    arr = numpy.arange(0, n)
    numpy.random.shuffle(arr)
    for i in range(0, p):
        a = arr[i % n]
        b = arr[(i+1) % n]
        m[a][b] = 1
        m[b][a] = 1

m = numpy.zeros(shape=(args.size,args.size))

# k = 0 => line pairs floating
# k = 1 => circle
p = max(1, args.connect * args.size)
l = int(numpy.ceil(args.size / p) * numpy.ceil(args.size/p))

for i in range(0,l):
    genline(m, args.size, int(p))

# Output
for i in range(0,args.size):
    for j in range(0,args.size):
        print int(m[i][j]),
    print
