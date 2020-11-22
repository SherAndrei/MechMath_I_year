set xrange [0:1]
set yrange [0:1]

set multiplot layout 1, 2;
set title "a = 10";
set size square 0.5,1
plot for [i = 0:3] 'input'.i.'.txt' with lines
set title "a = 1000";
set size square 0.5,1
plot for [i = 4:7] 'input'.i.'.txt' with lines
unset multiplot