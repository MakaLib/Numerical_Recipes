set term jpeg
set out 'wynik_dla_20.jpg'
set xlabel 'X'
set ylabel 'Y(X)'
plot 'dane.dat' u 1:2 w l t 'Dokladne',\
			''  u 3:4 w l t 'Wyznaczone',

