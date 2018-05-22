OS := $(shell uname -s)

all:
    ifeq ("$(OS)", "Darwin")
	g++ TrabalhoCG.cpp -o TrabalhoCG -framework OpenGL -framework GLUT
    else
	g++ TrabalhoCG.cpp -o TrabalhoCG -lGL -lGLU -lglut -lopenal -lalut -fpermissive -w

    endif

clean:
	rm -rf TrabalhoCG

run:
	./TrabalhoCG
