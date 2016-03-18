#!/bin/bash

## This shit it's not tested, the server is down for the moment.

if [ $# -eq 0 ]
then
    echo "Not enought arguments provided"
    read begin
else
    begin=$1
fi

lines=`grep :studs: /etc/passwd`

for line in lines
do
    user_name=`echo line | cut -f1 -d:`
    if [[ $user_name == $begin* ]]
    then
        htm_index="/fenrir/students/$user_name/public_html/index.htm"
        html_index="/fenrir/students/$user_name/public_html/index.html"
        php_index="/fenrir/students/$user_name/public_html/index.php"

        if test -e htm_index -o -e html_index -o -e php_index
        then
            echo "$user_name has a web page"
        fi
    fi
done
