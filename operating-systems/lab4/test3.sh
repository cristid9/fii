#!/bin/bash

if [ $1 -lt 1]
then
    echo "Nu-s destule argumente"
fi

for file in `find $1 -name "*.c++" -printf "%p\n"`
do
    if [ -f $file ]
    then
        echo `g++ $file`
    fi
done
