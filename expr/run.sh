#!/bin/bash


for VARIABLE in 1 2 3 4 5 6 7 8 9 10 
do
echo "Auth 1dim"
echo  $VARIABLE
./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
done
