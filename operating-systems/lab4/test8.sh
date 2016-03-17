# @brief Before reading this be aware that this is not the cleanest script
#        that I ever wrote.
#
#!/bin/bash

container=$*;

if [ $# -eq 0 ]
then
    container="";
    echo "How many arguments do you want to insert?";
    read number;

    while [ $number -gt 0 ]
    do
        read tmp;
        container=${container}${tmp}" ";
        number=$(( $number - 1 ));
    done

fi

container=( $container );

max_val=${container[0]};
max_oc=1;

for val in $container
do
    oc_current=0;
    for candidate in $container
    do
        if [ $candidate -eq $val ]
        then
            oc_current=$(( $oc_current + 1 ));
        fi
    done

    if [ $oc_current -gt $max_oc ]
    then
        max_val=$val;
        max_oc=$oc_current;
    fi
done

echo "$max_val appears $max_oc times in the provided string";
