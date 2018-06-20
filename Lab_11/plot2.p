set term jpeg
set out 'Rze_Uro.jpg'
set xlabel 'N'
set ylabel 'Y(N)'
plot 'rze_ur_8.dat' u 1:2 w l t 'Rzeczywiste',\
		'' u 1:3 w l t 'Urojone',\

set out 'Modulu.jpg'
plot 'rze_ur_8.dat' u 1:4 w l t 'Modul',\

set out 'zo10.jpg'
plot 'zo10.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'zaburzony',\

set out 'no10.jpg'
plot 'no10.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'niezaburzony',\

set out 'zo8.jpg'
plot 'zo8.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'zaburzony',\

set out 'no8.jpg'
plot 'no8.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'niezaburzony',\

set out 'zo12.jpg'
plot 'zo12.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'zaburzony',\

set out 'no12.jpg'
plot 'no12.dat' u 1:2 w l t 'splot',\
		'' u 1:3 w p t 'niezaburzony',\
