#!/bin/bash

if [ $# -lt 2 ]
then
    read current_dir
    read n
else
    current_dir=$1
    n=$2
fi

function print_last_n_lines ()
{
    files=`find "$1" -type f`
    for file in $files
    do
        perms=`ls -l "$file" | cut -b8,10`
        if [[ $perms == rx ]]
        then
            tail "-$2" "$file"
        fi
    done
}

print_last_n_lines $current_dir $n
