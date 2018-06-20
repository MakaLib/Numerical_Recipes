set term jpeg
set out 'wynik.jpg'
set xlabel 't'
set ylabel 'x(t)'
plot 'dane.dat' u 1:2 w p t 'x_num', 'dane.dat' u 1:3 w l t 'x_dok'
