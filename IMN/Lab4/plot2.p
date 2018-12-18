set term png
set out 'S(it)Globalna.png'
set xlabel 'it'
set ylabel 'S(it)'
set logscale x
set grid
plot 'globalna.dat' i 0 u 2:1 w l t 'wg = 0.6',\
	'' i 2 u 2:1 w l t 'wg = 1.0'

reset
set term png
set out 'PotencjalGlobalna.png'
set xlabel 'x'
set ylabel 'y'
set pm3d map
set palette defined (0 "blue", 5 "white", 10 "red")
set size ratio -1
splot [0:15][0:10][0:10] "globalna.dat" i 1 u 1:2:3


reset
set term png
set out 'BladGlobalna.png'
set xlabel 'x'
set ylabel 'y'
set pm3d map
set palette defined (0 "blue", 0.001 "green", 0.003 "red")
set palette rgbformulae 33,13,10
set size ratio -1
splot [0:15][0:10][0:0.003] "globalna.dat" i 1 u 1:2:4


reset
set term png
set out 'S(it)lokalna.png'
set xlabel 'it'
set ylabel 'S(it)'
set logscale x
set grid
plot 'lokalna.dat' i 0 u 2:1 w l t 'wl = 1.0',\
	'' i 1 u 2:1 w l t 'wl = 1.4',\
	'' i 2 u 2:1 w l t 'wl = 1.8',\
	'' i 3 u 2:1 w l t 'wl = 1.9'