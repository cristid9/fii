#!/bin/bash

container=( $* );
if [ $# -eq 0 ]
then
    echo "How long is the list?";
    read len;

    echo "Please insert the sequence: ";
    container="";
    
    while [ $len -gt 0 ]
    do
        read tmp;
        container=${container}${tmp}" ";
        len=$(( $len - 1 ));
    done
    container=( $container );
fi

length=${#container[@]};
N=${container[0]};

index=1;
partial_sum=0;
while [ $index -lt $length ]
do
    sum_index=$index;
    stop_index=$(( $index + $N ));
    partial_sum=0;

    while [ $sum_index -lt $stop_index -a $sum_index -lt $length ]
    do
        partial_sum=$(( $partial_sum + ${container[$sum_index]} ));
        sum_index=$(( $sum_index + 1 ));
        index=$(( $index + 1 ));
    done

    echo $partial_sum;
done

