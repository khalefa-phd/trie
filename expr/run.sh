#!/bin/bash

for VARIABLE in 10 9 8 7 6 5 4 3 2 1
do
echo "Auth"
echo  $VARIABLE


#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
#./v1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700

./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
./v2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700


#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
#./v1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660


./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
./v2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660

done