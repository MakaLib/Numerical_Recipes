set term jpeg
set out 'wynikr.jpg'
set xlabel 'Liczba iteracji'
set ylabel 'Norma euklidesowa wektora rozwiazan'
plot 'wynik.dat' u 1:2 w l t 'x(k)'
