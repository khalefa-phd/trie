#!/bin/bash

for VARIABLE in 10 9 8 7 6 5 4 3 2 1
do
echo "Auth"
echo  $VARIABLE


./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
./s1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700

./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
./s2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700


./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
./s1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660


./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
./s2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660

done