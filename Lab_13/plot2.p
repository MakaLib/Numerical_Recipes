set term jpeg
set out 'Wynik1.jpg'
set xlabel 'Iteracja'
set ylabel 'Roznica'
plot 'dane1.dat' u 1:2 w l t '',\

set out 'Wynik2a.jpg'
plot 'dane2a.dat' u 1:2 w l t '',\

set out 'Wynik2b.jpg'
plot 'dane2b.dat' u 1:2 w l t '',\

set out 'Wynik3.jpg'
plot 'dane3.dat' u 1:2 w l t '',\

set xlabel 'X'
set ylabel 'Y(X)'
set out 'GX.jpg'
plot 'gx.dat' u 1:2 w l t '',\