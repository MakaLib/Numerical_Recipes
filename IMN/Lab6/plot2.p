reset
set term png
set out 'NX50.png'
set xlabel 'x'
set ylabel 'y'
set pm3d map
set palette defined (-10 "blue", 0 "white", 10 "red")
set size ratio -1
splot [0:5.0][0:5.0][-10:10] "dane.dat" i 0 u 1:2:3


set out 'NX100.png'
splot [0:10.0][0:10.0][-10:10] "dane.dat" i 1 u 1:2:3

set out 'NX200.png'
splot [0:20.0][0:20.0][-10:10] "dane.dat" i 2 u 1:2:3

set cbrange [-0.8:0.8]
set palette defined (-0.8 "blue", 0 "white", 0.8 "red")
set out 'EPS1.png'
splot [0:10.0][0:10.0][-0.8:0.8] "dane.dat" i 3 u 1:2:3

set out 'EPS2.png'
splot [0:10.0][0:10.0][-0.8:0.8] "dane.dat" i 4 u 1:2:3

set out 'EPS10.png'
splot [0:10.0][0:10.0][-0.8:0.8] "dane.dat" i 5 u 1:2:3