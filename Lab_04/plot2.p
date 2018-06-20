set term jpeg
set out 'wynik2.jpg'
set key box outside
set xlabel 'x'
set ylabel 'wartości włanse wektora'
plot 'dane2.dat' u 1:2 w l t 'wek1', \
			''   u 1:3 w l t 'wek2', \
			''   u 1:4 w l t 'wek3', \
			''   u 1:5 w l t 'wek4', \
			''   u 1:6 w l t 'wek5', \
			''   u 1:7 w l t 'wek6'
set out 'wynik3.jpg'
plot 'dane3.dat' u 1:2 w l t 'wek1', \
			''   u 1:3 w l t 'wek2', \
			''   u 1:4 w l t 'wek3', \
			''   u 1:5 w l t 'wek4', \
			''   u 1:6 w l t 'wek5', \
			''   u 1:7 w l t 'wek6' 