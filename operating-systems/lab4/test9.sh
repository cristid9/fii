#!/bin/bash

retval=0
function fact ()
{
    if [ $1 -eq 1 -o $1 -eq 0 ]
    then
        retval=1;
        return 1;
    fi

    fact $(( $1 - 1 ));
    retval=$(( $retval * $1 ));
}


if [ $# -ne 2 ]
then
    echo "You haven't eterned the right number of arguments";
    echo "Insert n and k: ";
    read n;
    read k;
else
    n=$1;
    k=$2;
fi

if [ $n -lt $k ]
then
    echo "n can't be less than k";
    exit 1;
fi

fact $n
part1=$retval;

fact $k
part2=$retval;

fact $(( $n - $k ));
part3=$retval;

echo $(( $part1 / $(( $part2 * $part3 )) ));

