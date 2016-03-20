#!/bin/bash

if [ $# != 0 ]
then
    current_directory=$1
else
    read current_directory
fi

function rec_display_file_info ()
{
    for file in `ls -A`
    do
        if test -d $file
        then
            new_path=$1/$file
            rec_display_file_info $new_path
        fi

        if test -f $file
        then
            words=`wc -w $file | cut -f1 -d" "`
            characters=`wc -c $file | cut -f1 -d" "`
            echo "$file has $words words and $characters charcters"
        fi
    done
}

rec_display_file_info $current_directory
