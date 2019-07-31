#!/bin/bash
mkdir ../results

for VARIABLE in 1 2 3 4 5 6 7 8 9 10
do
echo  $VARIABLE

./s1dim ../data/EWords ../results/words_stat_ ../data/wiki10 $VARIABLE
./s2dim ../data/EWords ../results/words_stat_ ../data/wiki10 $VARIABLE


./s1dim ../data/Auth1M ../results/auth_stat_ ../data/Auth10 $VARIABLE
./s2dim ../data/Auth1M ../results/auth_stat ../data/Auth10 $VARIABLE
done
