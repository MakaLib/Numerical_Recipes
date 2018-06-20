set term jpeg
set out 'wynik.jpg'
set xlabel 'Numer iteracji - k'
set ylabel 'Przybliżenia wartości własnych'
plot 'dane.dat' u ($1 == 0 ? $2 : 1/0):3 w l t 'f1(k)',\
              '' u ($1 == 1 ? $2 : 1/0):3 w l t 'f2(k)',\
              '' u ($1 == 2 ? $2 : 1/0):3 w l t 'f3(k)',\
              '' u ($1 == 3 ? $2 : 1/0):3 w l t 'f4(k)',\
              '' u ($1 == 4 ? $2 : 1/0):3 w l t 'f5(k)',\
              '' u ($1 == 5 ? $2 : 1/0):3 w l t 'f6(k)',\
              '' u ($1 == 6 ? $2 : 1/0):3 w l t 'f7(k)'			
