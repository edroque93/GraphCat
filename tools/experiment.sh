#!/bin/bash

it=10
trials=10
pow2nodes=20

for p in $(seq 2 $pow2nodes)
do
	nodes=$((2**p))
	printf "$nodes,"
	acc=0.0
	for i in $(seq 1 $trials)
	do
		./matrix.py $nodes > temp.sparse
		res=`../graphcat -iters $it -topology temp.sparse -output output/ -animate no  | tail -n 1 | cut -d ' ' -f3`
		acc=`echo "$acc+$res" | bc`
	done
	acc=`echo "scale=5; $acc/$trials" | bc -l`
	printf "$acc \n"
done

rm temp.sparse
