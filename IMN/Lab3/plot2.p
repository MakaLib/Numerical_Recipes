set term jpeg
set out 'RKxt.jpg'
set xlabel 't'
set ylabel 'x'
set grid
plot 'Wyniki.dat' i 0 u 1:3 w l t 'x(t) TOL=-2',\
	'' i 1 u 1:3 w l t 'x(t) TOL=-5'

set out 'RKvt.jpg'
set ylabel 'v'
plot 'Wyniki.dat' i 0 u 1:4 w l t 'v(t) TOL=-2',\
	'' i 1 u 1:4 w l t 'v(t) TOL=-5'

set out 'RKdtt.jpg'
set ylabel 'dt'
plot 'Wyniki.dat' i 0 u 1:2 w l t 'dt(t) TOL=-2',\
	'' i 1 u 1:2 w l t 'dt(t) TOL=-5'

set out 'RKvx.jpg'
set ylabel 'v'
set xlabe 'x'
plot 'Wyniki.dat' i 0 u 3:4 w l t 'v(x) TOL=-2',\
	'' i 1 u 3:4 w l t 'x(t) TOL=-5'


set out 'Txt.jpg'
set xlabel 't'
set ylabel 'x'
plot 'Wyniki.dat' i 2 u 1:3 w l t 'x(t) TOL=-2',\
	'' i 3 u 1:3 w l t 'x(t) TOL=-5'

set out 'Tvt.jpg'
set ylabel 'v'
plot 'Wyniki.dat' i 2 u 1:4 w l t 'v(t) TOL=-2',\
	'' i 3 u 1:4 w l t 'v(t) TOL=-5'

set out 'Tdtt.jpg'
set ylabel 'dt'
plot 'Wyniki.dat' i 2 u 1:2 w l t 'dt(t) TOL=-2',\
	'' i 3 u 1:2 w l t 'dt(t) TOL=-5'

set out 'Tvx.jpg'
set ylabel 'v'
set xlabe 'x'
plot 'Wyniki.dat' i 2 u 3:4 w l t 'v(x) TOL=-2',\
	'' i 3 u 3:4 w l t 'x(t) TOL=-5'


