set term png
set o "vx.png"
set pm3d map
set palette defined ( 0 "white", 1 "red")
set cbrange[0:45]
sp "V.dat" u 1:2:3

set o "vy.png"
set palette defined (-1 "blue", 0 "white", 1 "red")
set cbrange[-20:20]
sp "V.dat" u 1:2:4

reset
set o "mapa1D0.png"
set pm3d map
splot "mapy.dat" i 0 u 1:2:3

set o "mapa2D0.png"
set pm3d map
splot "mapy.dat" i 1 u 1:2:3

set o "mapa3D0.png"
set pm3d map
splot "mapy.dat" i 2 u 1:2:3

set o "mapa4D0.png"
set pm3d map
splot "mapy.dat" i 3 u 1:2:3

set o "mapa5D0.png"
set pm3d map
splot "mapy.dat" i 4 u 1:2:3

set o "mapa1D1.png"
set pm3d map
splot "mapy.dat" i 5 u 1:2:3

set o "mapa2D1.png"
set pm3d map
splot "mapy.dat" i 6 u 1:2:3

set o "mapa3D1.png"
set pm3d map
splot "mapy.dat" i 7 u 1:2:3

set o "mapa4D1.png"
set pm3d map
splot "mapy.dat" i 8 u 1:2:3

set o "mapa5D1.png"
set pm3d map
splot "mapy.dat" i 9 u 1:2:3


