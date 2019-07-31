#!/bin/bash
mkdir ../results

for VARIABLE in 4 10
do
echo  $VARIABLE
./t1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
./t2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
done
