#/bin/bash

dirs=0
hidden_files=0
aliases=0

function walk_ ()
{
    for file in `ls -A $1`
    do

        if test -d $file
        then
            dirs=$(( $dirs + 1 ));
            new_path=$1/$file
            walk_ $new_path
        fi      

        if test -L $file
        then
            aliases=$(( $aliases + 1 ));
        fi

        if  test -f $file 
        then
            if [[ $file == .* ]]
            then
                hidden_files=$(( $hidden_files + 1 ));
            fi
        fi

    done
}

walk_ $1

echo "directoare: " $dirs
echo "aliasuri: " $aliases
echo "fisiere ascunse: " $hidden_files

