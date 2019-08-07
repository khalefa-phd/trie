#!/bin/bash 


mkdir -p combined

cat stat/auth*1dim*csv > combined/A_1dim.csv
cat stat/auth*2dim*csv > combined/A_2dim.csv
cat stat/words*1dim*csv > combined/W_1dim.csv
cat stat/words*2dim*csv > combined/W_2dim.csv

grep -v "\*\*\*" combined/A_1dim.csv |  sed 's/expr.cc/auth1d/g' |sed 's/,,/,/g' > combined/pA_1dim.csv

grep -v "\*\*\*" combined/A_2dim.csv |  sed 's/expr.cc/auth2d/g' |sed 's/,,/,/g' > combined/pA_2dim.csv

grep -v "\*\*\*" combined/W_1dim.csv |  sed 's/expr.cc/words1d/g' |sed 's/,,/,/g' > combined/pW_1dim.csv

grep -v "\*\*\*" combined/W_2dim.csv |  sed 's/expr.cc/words2d/g' |sed 's/,,/,/g' > combined/pW_2dim.csv

cat combined/p*csv > results1.csv

rm -fr combined

