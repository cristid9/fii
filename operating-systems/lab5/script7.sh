#!/bin/bash

if [ $# -eq 0 ]
then
    read current_dir
else
    current_dir=$1
fi

function print_scripts_comments ()
{
    for file in *.sh
    do
        grep -E '^#' "$file"
    done
}

print_scripts_comments $current_dir
