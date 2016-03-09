#!/bin/bash

fact=1
i=1

while [ $i -lt 5 ]
do
    fact=$(($fact * $i));
    i=$(($i + 1))
done

echo $fact
