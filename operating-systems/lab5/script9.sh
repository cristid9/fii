#!/bin/bash

if [ $# -eq 0 ]
then
    read current_dir
else
    current_dir=$1
fi

# Clean, isn't it?
find "$current_dir" -maxdepth 1 -type f -name "*.c" -exec gcc \{} \; 

