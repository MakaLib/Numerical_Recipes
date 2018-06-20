set term jpeg
set out 'Wynik1.jpg'
set xlabel 'x[i]'
set ylabel 'x[i+1]'
plot 'dane1.dat' u 1:2 w p t ''

set out 'Wynik2.jpg'
plot 'dane2.dat' u 1:2 w p t ''

set out 'Wynik3.jpg'
plot 'dane3.dat' u 1:2 w p t ''


set xlabel 'x[i]'
set ylabel 'x[i+2]'
set out 'Wynik1b.jpg'
plot 'dane1b.dat' u 1:2 w p t ''

set out 'Wynik2b.jpg'
plot 'dane2b.dat' u 1:2 w p t ''

set out 'Wynik3b.jpg'
plot 'dane3b.dat' u 1:2 w p t ''


set xlabel 'x[i]'
set ylabel 'x[i+3]'
set out 'Wynik1c.jpg'
plot 'dane1c.dat' u 1:2 w p t ''

set out 'Wynik2c.jpg'
plot 'dane2c.dat' u 1:2 w p t ''

set out 'Wynik3c.jpg'
plot 'dane3c.dat' u 1:2 w p t ''


set xlabel ''
set ylabel ''
set out 'Sfera.jpg'
set xyplane -1
set border 4095
splot 'sfera.dat' u 1:2:3 w p t ''

set out 'Kula.jpg'
splot 'kula.dat' u 1:2:3 w p t ''