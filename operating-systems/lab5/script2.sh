#/bin/bash

# hdjfhsdfjksdf dsfjsdjfhj

max_line_length=0

function rec_line_counter ()
{
    for file in `ls -A $1`
    do
        if test -d $file
        then   
            new_path=$1/$file
            rec_line_counter $new_path  
        fi

        if test -f $file
        then
            extended_encoding=`file $file --mime-encoding` 
            if [[ $extended_encoding == *ascii* ]]
            then

                current_len=`wc -L $file | cut -f1 -d" " `
                if [ $max_line_length -lt $current_len ]                
                then
                    max_line_length=$current_len
                fi

            fi
        fi

    done
}

rec_line_counter $1
echo $max_line_length

