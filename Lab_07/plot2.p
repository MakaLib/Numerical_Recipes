set term jpeg
set out 'wynik.jpg'
set xlabel 'X'
set ylabel 'Y(X)'
plot 'dane.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynik1.jpg'
plot 'dane1.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynik2.jpg'
plot 'dane2.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynik3.jpg'
plot 'dane3.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynikcz.jpg'
plot 'danecz.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynikcz1.jpg'
plot 'dane1cz.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynikcz2.jpg'
plot 'dane2cz.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',

set out 'wynikcz3.jpg'
plot 'dane3cz.dat' u 2:3 w l t 'f(x)',\
			''  u 4:5 w l t 'W(x)',