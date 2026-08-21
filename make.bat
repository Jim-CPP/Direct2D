cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Direct2D.cpp Direct2DClass.cpp -o Direct2D.exe -ld2d1
