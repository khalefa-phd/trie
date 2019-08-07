#!/bin/bash

grep auth1d a.csv > auth1d.csv
grep auth2d a.csv > auth2d.csv
grep words1d a.csv > words1d.csv
grep words2d a.csv > words2d.csv

awk --field-separator="," '{if ($3=="1") print $0 ;}' auth1d.csv > auth1d_q1.csv
awk --field-separator="," '{if ($3=="2") print $0 ;}' auth1d.csv > auth1d_q2.csv
awk --field-separator="," '{if ($3=="3") print $0 ;}' auth1d.csv > auth1d_q3.csv
awk --field-separator="," '{if ($3=="4") print $0 ;}' auth1d.csv > auth1d_q4.csv
awk --field-separator="," '{if ($3=="5") print $0 ;}' auth1d.csv > auth1d_q5.csv
awk --field-separator="," '{if ($3=="6") print $0 ;}' auth1d.csv > auth1d_q6.csv
awk --field-separator="," '{if ($3=="7") print $0 ;}' auth1d.csv > auth1d_q7.csv
awk --field-separator="," '{if ($3=="8") print $0 ;}' auth1d.csv > auth1d_q8.csv
awk --field-separator="," '{if ($3=="9") print $0 ;}' auth1d.csv > auth1d_q9.csv
awk --field-separator="," '{if ($3=="10") print $0 ;}' auth1d.csv > auth1d_q10.csv


awk --field-separator="," '{if ($2=="1") print $0 ;}' auth1d.csv > auth1d_k1.csv
awk --field-separator="," '{if ($2=="2") print $0 ;}' auth1d.csv > auth1d_k2.csv
awk --field-separator="," '{if ($2=="4") print $0 ;}' auth1d.csv > auth1d_k4.csv
awk --field-separator="," '{if ($2=="8") print $0 ;}' auth1d.csv > auth1d_k8.csv
awk --field-separator="," '{if ($2=="16") print $0 ;}' auth1d.csv > auth1d_k16.csv
awk --field-separator="," '{if ($2=="32") print $0 ;}' auth1d.csv > auth1d_k32.csv
awk --field-separator="," '{if ($2=="64") print $0 ;}' auth1d.csv > auth1d_k64.csv
awk --field-separator="," '{if ($2=="128") print $0 ;}' auth1d.csv > auth1d_k128.csv
awk --field-separator="," '{if ($2=="256") print $0 ;}' auth1d.csv > auth1d_k256.csv
awk --field-separator="," '{if ($2=="512") print $0 ;}' auth1d.csv > auth1d_k512.csv
awk --field-separator="," '{if ($2=="1024") print $0 ;}' auth1d.csv > auth1d_k1024.csv
awk --field-separator="," '{if ($2=="10240") print $0 ;}' auth1d.csv > auth1d_k10240.csv
awk --field-separator="," '{if ($2=="20480") print $0 ;}' auth1d.csv > auth1d_k20480.csv


awk --field-separator="," '{if ($3=="1") print $0 ;}' auth2d.csv > auth2d_q1.csv
awk --field-separator="," '{if ($3=="2") print $0 ;}' auth2d.csv > auth2d_q2.csv
awk --field-separator="," '{if ($3=="3") print $0 ;}' auth2d.csv > auth2d_q3.csv
awk --field-separator="," '{if ($3=="4") print $0 ;}' auth2d.csv > auth2d_q4.csv
awk --field-separator="," '{if ($3=="5") print $0 ;}' auth2d.csv > auth2d_q5.csv
awk --field-separator="," '{if ($3=="6") print $0 ;}' auth2d.csv > auth2d_q6.csv
awk --field-separator="," '{if ($3=="7") print $0 ;}' auth2d.csv > auth2d_q7.csv
awk --field-separator="," '{if ($3=="8") print $0 ;}' auth2d.csv > auth2d_q8.csv
awk --field-separator="," '{if ($3=="9") print $0 ;}' auth2d.csv > auth2d_q9.csv
awk --field-separator="," '{if ($3=="10") print $0 ;}' auth2d.csv > auth2d_q10.csv


awk --field-separator="," '{if ($2=="1") print $0 ;}' auth2d.csv > auth2d_k1.csv
awk --field-separator="," '{if ($2=="2") print $0 ;}' auth2d.csv > auth2d_k2.csv
awk --field-separator="," '{if ($2=="4") print $0 ;}' auth2d.csv > auth2d_k4.csv
awk --field-separator="," '{if ($2=="8") print $0 ;}' auth2d.csv > auth2d_k8.csv
awk --field-separator="," '{if ($2=="16") print $0 ;}' auth2d.csv > auth2d_k16.csv
awk --field-separator="," '{if ($2=="32") print $0 ;}' auth2d.csv > auth2d_k32.csv
awk --field-separator="," '{if ($2=="64") print $0 ;}' auth2d.csv > auth2d_k64.csv
awk --field-separator="," '{if ($2=="128") print $0 ;}' auth2d.csv > auth2d_k128.csv
awk --field-separator="," '{if ($2=="256") print $0 ;}' auth2d.csv > auth2d_k256.csv
awk --field-separator="," '{if ($2=="512") print $0 ;}' auth2d.csv > auth2d_k512.csv
awk --field-separator="," '{if ($2=="1024") print $0 ;}' auth2d.csv > auth2d_k1024.csv
awk --field-separator="," '{if ($2=="10240") print $0 ;}' auth2d.csv > auth2d_k10240.csv
awk --field-separator="," '{if ($2=="20480") print $0 ;}' auth2d.csv > auth2d_k20480.csv



awk --field-separator="," '{if ($3=="1") print $0 ;}' words1d.csv > words1d_q1.csv
awk --field-separator="," '{if ($3=="2") print $0 ;}' words1d.csv > words1d_q2.csv
awk --field-separator="," '{if ($3=="3") print $0 ;}' words1d.csv > words1d_q3.csv
awk --field-separator="," '{if ($3=="4") print $0 ;}' words1d.csv > words1d_q4.csv
awk --field-separator="," '{if ($3=="5") print $0 ;}' words1d.csv > words1d_q5.csv
awk --field-separator="," '{if ($3=="6") print $0 ;}' words1d.csv > words1d_q6.csv
awk --field-separator="," '{if ($3=="7") print $0 ;}' words1d.csv > words1d_q7.csv
awk --field-separator="," '{if ($3=="8") print $0 ;}' words1d.csv > words1d_q8.csv
awk --field-separator="," '{if ($3=="9") print $0 ;}' words1d.csv > words1d_q9.csv
awk --field-separator="," '{if ($3=="10") print $0 ;}' words1d.csv > words1d_q10.csv


awk --field-separator="," '{if ($2=="1") print $0 ;}' words1d.csv > words1d_k1.csv
awk --field-separator="," '{if ($2=="2") print $0 ;}' words1d.csv > words1d_k2.csv
awk --field-separator="," '{if ($2=="4") print $0 ;}' words1d.csv > words1d_k4.csv
awk --field-separator="," '{if ($2=="8") print $0 ;}' words1d.csv > words1d_k8.csv
awk --field-separator="," '{if ($2=="16") print $0 ;}' words1d.csv > words1d_k16.csv
awk --field-separator="," '{if ($2=="32") print $0 ;}' words1d.csv > words1d_k32.csv
awk --field-separator="," '{if ($2=="64") print $0 ;}' words1d.csv > words1d_k64.csv
awk --field-separator="," '{if ($2=="128") print $0 ;}' words1d.csv > words1d_k128.csv
awk --field-separator="," '{if ($2=="256") print $0 ;}' words1d.csv > words1d_k256.csv
awk --field-separator="," '{if ($2=="512") print $0 ;}' words1d.csv > words1d_k512.csv
awk --field-separator="," '{if ($2=="1024") print $0 ;}' words1d.csv > words1d_k1024.csv
awk --field-separator="," '{if ($2=="10240") print $0 ;}' words1d.csv > words1d_k10240.csv
awk --field-separator="," '{if ($2=="20480") print $0 ;}' words1d.csv > words1d_k20480.csv

awk --field-separator="," '{if ($3=="1") print $0 ;}' words2d.csv > words2d_q1.csv
awk --field-separator="," '{if ($3=="2") print $0 ;}' words2d.csv > words2d_q2.csv
awk --field-separator="," '{if ($3=="3") print $0 ;}' words2d.csv > words2d_q3.csv
awk --field-separator="," '{if ($3=="4") print $0 ;}' words2d.csv > words2d_q4.csv
awk --field-separator="," '{if ($3=="5") print $0 ;}' words2d.csv > words2d_q5.csv
awk --field-separator="," '{if ($3=="6") print $0 ;}' words2d.csv > words2d_q6.csv
awk --field-separator="," '{if ($3=="7") print $0 ;}' words2d.csv > words2d_q7.csv
awk --field-separator="," '{if ($3=="8") print $0 ;}' words2d.csv > words2d_q8.csv
awk --field-separator="," '{if ($3=="9") print $0 ;}' words2d.csv > words2d_q9.csv
awk --field-separator="," '{if ($3=="10") print $0 ;}' words2d.csv > words2d_q10.csv


awk --field-separator="," '{if ($2=="1") print $0 ;}' words2d.csv > words2d_k1.csv
awk --field-separator="," '{if ($2=="2") print $0 ;}' words2d.csv > words2d_k2.csv
awk --field-separator="," '{if ($2=="4") print $0 ;}' words2d.csv > words2d_k4.csv
awk --field-separator="," '{if ($2=="8") print $0 ;}' words2d.csv > words2d_k8.csv
awk --field-separator="," '{if ($2=="16") print $0 ;}' words2d.csv > words2d_k16.csv
awk --field-separator="," '{if ($2=="32") print $0 ;}' words2d.csv > words2d_k32.csv
awk --field-separator="," '{if ($2=="64") print $0 ;}' words2d.csv > words2d_k64.csv
awk --field-separator="," '{if ($2=="128") print $0 ;}' words2d.csv > words2d_k128.csv
awk --field-separator="," '{if ($2=="256") print $0 ;}' words2d.csv > words2d_k256.csv
awk --field-separator="," '{if ($2=="512") print $0 ;}' words2d.csv > words2d_k512.csv
awk --field-separator="," '{if ($2=="1024") print $0 ;}' words2d.csv > words2d_k1024.csv
awk --field-separator="," '{if ($2=="10240") print $0 ;}' words2d.csv > words2d_k10240.csv
awk --field-separator="," '{if ($2=="20480") print $0 ;}' words2d.csv > words2d_k20480.csv
