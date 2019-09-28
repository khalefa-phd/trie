#!/bin/bash

for VARIABLE in 10 9 8 7 6 5 4 3 2 1
do
echo "Auth"
echo  $VARIABLE


 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
 ./oe1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700

 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
 ./oe2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700


 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
 ./oe1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660


 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
 ./oe2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660

done