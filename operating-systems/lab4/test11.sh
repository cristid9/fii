#!/bin/bash

real_name=`grep $1 /etc/passwd | cut -f5 -d":"`
echo "The real name is $real_name"

user_name=`grep $1 /etc/passwd | cut -f1 -d":"`

# He didn't say that I can't use this command
echo `groups $user_name`
