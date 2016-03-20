#!/bin/bash

output_file=""

if [ $# == 0 ]
then
    read output_file
else
    output_file=$1
fi

operations=0
condition=true

while [ $condition == true ]
do
    read a
    read b
    read op

    if [ $op != "q" ]
    then
        result=$(($a $op $b))
        echo "$operations: $a $op $b = $result" >> $output_file
        operations=$(( $operations + 1 ))
    else
        condition=false
    fi
done

echo $operations >> $output_file
