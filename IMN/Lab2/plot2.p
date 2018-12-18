set term jpeg
set out 'Picard.jpg'
set xlabel 't'
set ylabel 'u'
set grid
plot 'Wyniki.dat' i 0 u 1:2 w l t 'u(t)',\
	'Wyniki.dat' i 0 u 1:3 w l t 'z(t)'

set out 'Newton.jpg'
plot 'Wyniki.dat' i 1 u 1:2 w l t 'u(t)',\
	'Wyniki.dat' i 1 u 1:3 w l t 'z(t)'

set out 'RK2.jpg'
plot 'Wyniki.dat' i 2 u 1:2 w l t 'u(t)',\
	'Wyniki.dat' i 2 u 1:3 w l t 'z(t)'
