set terminal postscript color enhanced eps font "Arial-Bold,32";
set key top left;
set pointsize 4;

set xlabel "k" offset 0,0.5;
set ylabel "Time (msec)" offset 1,0;
#set ytics ("2" 2000, "4" 4000, "6" 6000, "8" 8000)
#set xtics ("10:10" 10000, "30:30" 30000)


set style line 1 lt 1 dt 1 lw 2 pt 9 lc rgb "red";
set style line 2 lt 1 dt 2 lw 2 pt 4 lc rgb "blue';
set style line 3 lt 1 dt 2 lw 2 pt 1 lc rgb "black";
set datafile separator ","

set xrange [1:240]
set logscale y

set output 'auth1d_q1.eps';

plot 'auth1d_q1.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_q2.eps';

plot 'auth1d_q2.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q3.eps';

plot 'auth1d_q3.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q4.eps';

plot 'auth1d_q4.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q5.eps';

plot 'auth1d_q5.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;



set output 'auth1d_q6.eps';

plot 'auth1d_q6.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q7.eps';

plot 'auth1d_q7.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q8.eps';

plot 'auth1d_q8.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_q9.eps';

plot 'auth1d_q9.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;



set output 'auth1d_q10.eps';

plot 'auth1d_q10.csv' using 2:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 2:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 2:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set xlabel "Q" offset 0,0.5;

set logscale x
set xrange[1:250]
set output 'auth1d_k1.eps';

plot 'auth1d_k1.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k1.eps';

plot 'auth1d_k1.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k2.eps';

plot 'auth1d_k2.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k4.eps';

plot 'auth1d_k4.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k8.eps';

plot 'auth1d_k8.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k16.eps';

plot 'auth1d_k16.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k32.eps';

plot 'auth1d_k32.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k64.eps';

plot 'auth1d_k64.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k128.eps';

plot 'auth1d_k128.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k256.eps';

plot 'auth1d_k256.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k512.eps';

plot 'auth1d_k512.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k1024.eps';

plot 'auth1d_k1024.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;


set output 'auth1d_k10240.eps';

plot 'auth1d_k10240.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;

set output 'auth1d_k20480.eps';

plot 'auth1d_k20480.csv' using 3:($4/1000/1000) title 'Meta' with linespoints ls 1, '' using 3:($5/1000/1000) title 'Depth' with linespoints ls 2,'' using 3:($6/1000/1000) title 'iDepth' with linespoints ls 3;







