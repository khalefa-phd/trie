#!/bin/bash


for VARIABLE in 1 2 3 4 5 6 7 8 9 10 
do
echo "Auth"
echo  $VARIABLE
./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE


./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
done
