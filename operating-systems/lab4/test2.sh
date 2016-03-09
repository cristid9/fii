#!/bin/bash

result=1
retval=1
function fact ()
{
    if [ $1 -eq 0 ]
    then
        retval=1
    fi

    if [ $1 -eq 1 ]
    then
        retval=1
    fi
    
    if [ $1 -gt 1 ]
    then
        result=$(( $result * $1 ))
        fact $(( $1 - 1 ))
    fi
}

if [ $# -lt 1 ]
then
    echo "n= "
    read n
else
    n=$1
fi

fact $n
echo $result
