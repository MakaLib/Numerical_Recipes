set term jpeg
set out 'wynik.jpg'
set yrange [0 : 0.2]
set xlabel 'α'
set ylabel 'częstość własna drgań (ω)'
plot 'dane1.dat' u 1:2 w l t 'f1(α)', \
			''   u 1:3 w l t 'f2(α)', \
			''   u 1:4 w l t 'f3(α)', \
			''   u 1:5 w l t 'f4(α)', \
			''   u 1:6 w l t 'f5(α)', \
			''   u 1:7 w l t 'f6(α)', 
