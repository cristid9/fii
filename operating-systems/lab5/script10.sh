#!/bin/bash

for file in *.txt
do
    root_name=${file%.*}
    mv "$file" "${root_name}.ascii"
done

