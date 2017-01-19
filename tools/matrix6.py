#!/usr/bin/python

import sys
import numpy
import argparse

parser = argparse.ArgumentParser(description='Create a nice random graph.')
parser.add_argument('-n', action='store', default=10, dest='size', type=int, help='size of matrix')
parser.add_argument('-d', action='store', default=0.1, dest='delta', type=float, help='delta')
parser.add_argument('-c', action='store_true', dest='connect', help='connect all nodes')
parser.add_argument('-nc', action='store_false', dest='connect')
parser.set_defaults(connect=True)

args = parser.parse_args(sys.argv[1:])

def connect(m,n,k):
    arr = numpy.arange(0, n)
    numpy.random.shuffle(arr)
    for i in range(0, k):
        a = arr[i % n]
        b = arr[(i+1) % n]
        m[a][b] = 1
        m[b][a] = 1

def genpoint():
    r = numpy.random.random();
    theta = 2 * numpy.pi * numpy.random.random()
    return numpy.array([r * numpy.cos(theta), r* numpy.sin(theta)])

m = numpy.zeros(shape=(args.size,args.size))
pts = [ genpoint() for i in range(0, args.size) ]

for i in range(0, args.size):
    for j in range(i+1, args.size):
        dist = numpy.linalg.norm(pts[i] - pts[j])
        if dist <= args.delta:
            m[i][j] = 1
            m[j][i] = 1

if args.connect:
    connect(m, args.size, args.size-1)

# Output
for i in range(0,args.size):
    for j in range(0,args.size):
        print int(m[i][j]),
    print
