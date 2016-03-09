#!/bin/bash

# i)
function multiply ()
{
    sum=0
    counter=$2

    while [ $counter -gt 0 ]
    do
        sum=$(( $sum + $1))
        counter=$(( $counter - 1 ))
    done

    return $sum
}

# ii)
function pow ()
{
    current_pow=1
    counter_2=$2

    while [ $counter_2 -gt 0 ]
    do
        multiply $current_pow $1
        current_pow=$?
        counter_2=$(( $counter_2 - 1 ))
    done

    return $current_pow
}

pow 2 3
echo $?
