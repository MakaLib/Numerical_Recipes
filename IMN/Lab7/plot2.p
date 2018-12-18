reset
set term png
set out 'Q-1000W.png'
set xlabel 'x'
set ylabel 'y'
set style increment userstyles 
set contour
set cntrparam levels 40
unset surface
set view map
unset key
sp "kontury.dat" i 0 u  1:2:3 w l lt -1 palette  t '' 


set out 'Q-1000S.png'
set palette defined (-200 "blue", 0 "green", 350 "red")
splot [0:10.0][0:10.0][-200:350] "kontury.dat" i 1 u 1:2:3
