#!/bin/bash

#Compiling C programs
for x in *.c
do
	gcc -Wall -Werror $x -lm -o `basename $x .c` || exit
done

#Checking parameters
if (( $# < 2 )); then
	echo "Usage: $0 <input> <output>"
	exit
fi

input="$1"
output="$2"
gap_length=0.5

mkdir -p "$output"
sox "$input" -r 6800 -c 1 -t dat - sinc 600-2800 norm -3 | tail -n+3 | ./demod | sox -t dat -r 3400 - -t dat -r 19200 - | tail -n+3 |./uart | ./split_to_files $gap_length "$output"

#deleting C compilates
for x in *.c
do
	rm `basename $x .c`
done

