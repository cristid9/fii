#!/bin/bash

fifos=0
subdirs=0

function count_fifos_and_subdirs ()
{
    for file in `ls -A $1`
    do
        if test -d $file
        then
            let subdirs++
            new_path=$1/$file
            count_fifos_and_subdirs $new_path
        
        fi

        if test -p $file
        then
            let fifos++
        fi

    done
}

if [ $# != 0 ]
then
    current_directory=$1
else
    read current_directory
fi

count_fifos_and_subdirs $current_directory

echo "Subdirectories: $subdirs"
echo "Fifos: $fifos"
