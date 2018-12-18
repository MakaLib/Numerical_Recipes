set term png
set out 'CiX.png'
set xlabel 't'
set ylabel 'x(t) c(t)'
set grid
plot 'CiX0.dat' i 0 u 3:2 w l t 'x(t) D= 0.0',\
	'' i 0 u 3:1 w l t 'c(t) D = 0.0',\
	'' i 1 u 3:2 w l t 'x(t) D = 0.1',\
	'' i 1 u 3:1 w l t 'x(t) D = 0.1'