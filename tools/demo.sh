#!/bin/bash

rm output/$1*.png
./graphcat -topology data/$1.csv -output output/$1 -animate yes
convert -delay 10 -loop 0 output/$1*.png demo/$1.gif
gifview -a demo/$1.gif
