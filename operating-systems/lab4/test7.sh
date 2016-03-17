#!/bin/bash

if [ $# -eq 0 ]
then
    echo "No argument provided";
    exit 1;
fi

if [ $1 -le 2 ]
then
    echo 1;
    exit 0;
fi

prev1=1;
prev2=1;
iterations=$1;

while [ $iterations -gt 2 ]
do
    tmp=$prev1; 
    prev1=$prev2;
    prev2=$(( $prev2 + $tmp ));
    iterations=$(( $iterations - 1 ));

done


echo "The value is: $prev2";
