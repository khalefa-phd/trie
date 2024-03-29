#!/bin/bash 


mkdir -p combined

cat results/auth*1dim*csv > combined/A_1dim.csv
cat results/auth*2dim*csv > combined/A_2dim.csv
cat results/words*1dim*csv > combined/W_1dim.csv
cat results/words*2dim*csv > combined/W_2dim.csv

grep -v "\*\*\*" combined/A_1dim.csv |  sed 's/expr.cc/auth1d/g' |sed 's/,,/,/g' > combined/pA_1dim.csv

grep -v "\*\*\*" combined/A_2dim.csv |  sed 's/expr.cc/auth2d/g' |sed 's/,,/,/g' > combined/pA_2dim.csv

grep -v "\*\*\*" combined/W_1dim.csv |  sed 's/expr.cc/words1d/g' |sed 's/,,/,/g' > combined/pW_1dim.csv

grep -v "\*\*\*" combined/W_2dim.csv |  sed 's/expr.cc/words2d/g' |sed 's/,,/,/g' > combined/pW_2dim.csv

cat combined/p*csv > a.csv

awk --field-separator="," '{if (NF==8) print  $o, ",,,"; else print $0 ;}' a.csv  > tmp.csv
awk --field-separator="," '{if (NF==10) print  $o, ","; else print $0 ;}' tmp.csv  > expr.csv


rm -fr combined a.csv tmp.csv

