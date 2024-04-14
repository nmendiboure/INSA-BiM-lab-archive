CXXFLAGS= -Wall
objects = noeud.o arbre.o main.o

all: main

main: $(objects)
	g++ $(CXXFLAGS) -o main $(objects)

main.o: main.cpp
	g++ $(CXXFLAGS) -o main.o -c main.cpp

arbre.o : arbre.cpp arbre.h
	g++ $(CXXFLAGS) -c -o arbre.o arbre.cpp	

noeud.o: noeud.cpp noeud.h
	g++ $(CXXFLAGS) -c -o noeud.o noeud.cpp

clean:
	rm $(objects) 
