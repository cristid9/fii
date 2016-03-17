#!/bin/bash

if [ $# -eq 0 ]
then
    echo "No arguments passed! ";
    exit 1;
fi

min_val=$1
max_val=$1

while [ $# -gt 0 ]
do
    if [ $1 -gt $max_val ]
    then
        max_val=$1;
    fi

    if [ $1 -lt $min_val ]
    then
        min_val=$1;
    fi

    shift 1;
done

echo "The maximum value is $max_val";
echo "The minimum value is $min_val";
