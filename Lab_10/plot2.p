set term jpeg
set out 'Wykres_2_pow.jpg'
set xlabel 'Numer iteracji'
set ylabel 'Prybliżenie'
plot 'dane_2_pow.dat' u 1:2 w l t '',\

