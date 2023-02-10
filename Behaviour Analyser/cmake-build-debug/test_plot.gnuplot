set terminal svg noenhanced linewidth 0.75 size 1024,768
set output "test_plot.gnuplot.svg"
set title "This is an example GnuPlot using vectors"
set autoscale
set xlabel "horizontal axis"
show xlabel
set xlabel "horizontal axis"
show ylabel
set cblabel "3rd axis (colour)"
set palette defined (0 "black", 2.5 "blue", 5 "red", 10 "yellow")
plot '-' with vectors nohead linecolor palette z title "test data sequence"
1, 0, 0, 19, 0.500000
1, 19, 18, 0, 0.500000
19, 19, 0, -18, 0.500000
19, 1, -17, 0, 0.500000
2, 1, 0, 17, 1.000000
2, 18, 16, 0, 1.000000
18, 18, 0, -16, 1.000000
18, 2, -15, 0, 1.000000
3, 2, 0, 15, 1.500000
3, 17, 14, 0, 1.500000
17, 17, 0, -14, 1.500000
17, 3, -13, 0, 1.500000
4, 3, 0, 13, 2.000000
4, 16, 12, 0, 2.000000
16, 16, 0, -12, 2.000000
16, 4, -11, 0, 2.000000
5, 4, 0, 11, 2.500000
5, 15, 10, 0, 2.500000
15, 15, 0, -10, 2.500000
15, 5, -9, 0, 2.500000
6, 5, 0, 9, 3.000000
6, 14, 8, 0, 3.000000
14, 14, 0, -8, 3.000000
14, 6, -7, 0, 3.000000
7, 6, 0, 7, 3.500000
7, 13, 6, 0, 3.500000
13, 13, 0, -6, 3.500000
13, 7, -5, 0, 3.500000
8, 7, 0, 5, 4.000000
8, 12, 4, 0, 4.000000
12, 12, 0, -4, 4.000000
12, 8, -3, 0, 4.000000
9, 8, 0, 3, 4.500000
9, 11, 2, 0, 4.500000
11, 11, 0, -2, 4.500000
11, 9, -1, 0, 4.500000