#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Nu ai introdus niciun numar"
    exit
fi

divide=$#
nr_args=$#
sum=0

while [ $nr_args -gt 0 ]
do
    sum=$(( $sum + $1 ))
    shift
    nr_args=$(( $nr_args - 1 ))
done

echo $(( $sum / $divide ))

