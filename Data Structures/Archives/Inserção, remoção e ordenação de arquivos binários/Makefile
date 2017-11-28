CPP = g++
CPPFLAGS = -Wall

OBJ = main.o deus.o arquivo.o excecao.o

main: $(OBJ)
	$(CPP) $(OBJ) -o main

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o

deus.o: deus.cpp deus.hpp
	$(CPP) -c deus.cpp -o deus.o

arquivo.o: arquivo.cpp arquivo.hpp
	$(CPP) -c arquivo.cpp -o arquivo.o

excecao.o: excecao.cpp excecao.hpp
	$(CPP) -c excecao.cpp -o excecao.o

all: main

clean:
	find . -type f | xargs touch
	rm -f *.o

