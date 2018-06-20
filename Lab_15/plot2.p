set term jpeg
set out 'Wynik0.jpg'
set xlabel 'V[m]'
set ylabel 'g[m]'
plot 'dane0.dat' u 1:2 w boxes lt '',\
	'dane0f.dat' u 1:2 w l t ''

set out 'Wynik1.jpg'
plot 'dane1.dat' u 1:2 w boxes lt '',\
	'dane1f.dat' u 1:2 w l t ''

set out 'Wynik2.jpg'
plot 'dane2.dat' u 1:2 w boxes lt '',\
	'dane2f.dat' u 1:2 w l t ''

set out 'Wynik3.jpg'
plot 'dane3.dat' u 1:2 w boxes lt '',\
	'dane3f.dat' u 1:2 w l t ''

