#!/usr/bin/python

import sys
import numpy
import argparse

parser = argparse.ArgumentParser(description='Create a random circle graph.')
parser.add_argument('-n', action='store', default=10, dest='size', type=int, help='size of matrix')
parser.add_argument('-l', action='store', default=2, dest='lvl', type=int, help='levels')

args = parser.parse_args(sys.argv[1:])

def genline(m,n,k):
    arr = numpy.arange(0, n)
    numpy.random.shuffle(arr)
    for i in range(1, k):
        m[arr[i-1]][arr[i]] = 1
        m[arr[i]][arr[i-1]] = 1

m = numpy.zeros(shape=(args.size,args.size))
k = args.size

# Generate lines
for i in range(0, args.lvl):
    genline(m, args.size, k)
    k = k / 2

# Output
for i in range(0,args.size):
    for j in range(0,args.size):
        print int(m[i][j]),
    print
