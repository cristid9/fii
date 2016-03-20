#!/bin/bash

if [ $# -eq 0 ]
then
    read current_dir
else
    current_dir=$1
fi

function print_tree_representation ()
{
    for file in `ls -A $1`
    do
        local times_p=$2
        while [ $times_p -gt 0 ]
        do
            echo  -n "---- "
            times_p=$(( $times_p - 1 ))
        done
        echo $file

        if test -d "$1/$file"
        then
            local new_path=$1/$file
            local new_depth=$(( $2 + 1 ))

            print_tree_representation $new_path $new_depth        
        fi
    done
}

print_tree_representation $current_dir 0

