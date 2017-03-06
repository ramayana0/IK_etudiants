IncPath = -I /usr/include -I .
#LibPath = -L /usr/lib
Options = $(IncPath) $(LibPath) -g

main : main.o
	g++ $(Options) main.o -o main -lGL -lglut -lGLU -L/usr/X11R6/lib -lX11 -lXmu -lXext -lXi -lm -lXxf86vm

main.o : main.cc  SceneGraph/*.h *.h Math/*.h
	g++ $(Options) -c main.cc
