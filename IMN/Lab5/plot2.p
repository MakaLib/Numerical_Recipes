set term png
set out 'S(it).png'
set xlabel 'it'
set ylabel 'S(it)'
set grid
plot 'blad.dat' i 0 u 1:2 w l t 'k = 16',\
	'' i 1 u 1:2 w l t 'k = 8',\
	'' i 2 u 1:2 w l t 'k = 4',\
	'' i 3 u 1:2 w l t 'k = 2',\
	'' i 4 u 1:2 w l t 'k = 1'

reset
set term png
set out 'Potencjal16.png'
set xlabel 'x'
set ylabel 'y'
set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")
set size ratio -1
splot [0:25.6][0:25.6][-1:1] "dane.dat" i 0 u 1:2:3


set out 'Potencjal8.png'
splot [0:25.6][0:25.6][-1:1] "dane.dat" i 1 u 1:2:3

set out 'Potencjal4.png'
splot [0:25.6][0:25.6][-1:1] "dane.dat" i 2 u 1:2:3

set out 'Potencjal2.png'
splot [0:25.6][0:25.6][-1:1] "dane.dat" i 3 u 1:2:3

set out 'Potencjal1.png'
splot [0:25.6][0:25.6][-1:1] "dane.dat" i 4 u 1:2:3