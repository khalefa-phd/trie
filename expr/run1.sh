#!/bin/bash
mkdir ../results

for VARIABLE in 4 10
do
echo "Auth 1dim"
echo  $VARIABLE
#./m1dimo ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
#./1dim_basio ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE
done
