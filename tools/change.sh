#!/bin/sh

file=$1
field=$2
value=$3

mv $file tmp.txt
awk "/$field/{print \"$field = $value\"} !/$field/" tmp.txt | tee $file
rm tmp.txt

