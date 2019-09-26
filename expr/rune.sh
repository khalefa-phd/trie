#!/bin/bash

for VARIABLE in 10 9 8 7 6 5 4 3 2 1
do
echo "Auth"
echo  $VARIABLE


 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
 ./e1dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700

 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 0 100
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 100 200
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 200 300
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 300 400
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 400 500
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 500 600
 ./e2dim ../data/EWords ../results/words_ ../data/wiki10 $VARIABLE 600 700


 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
 ./e1dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660


 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 0 99
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 100 200
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 200 300
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 300 400
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 400 500
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 500 600 
 ./e2dim ../data/Auth1M ../results/auth_ ../data/Auth10 $VARIABLE 600 660

done