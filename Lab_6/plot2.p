set term jpeg
set out 'wynik.jpg'
set xlabel 'Real'
set ylabel 'Imaginary'
plot 'dane.dat' u 5:6 w l t 'z = 0 + 0I',

set out 'wynik1.jpg'
plot 'dane1.dat' u 5:6 w l t 'z = -10 - 10I',