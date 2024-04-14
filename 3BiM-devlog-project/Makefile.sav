CXXFLAGS= -Wall
objects_tests = noeud.o google_tests.o arbre.o
objects_main = noeud.o arbre.o main.o
objects = noeud.o arbre.o main.o google_tests.o

all: run_tests main

run_tests: $(objects_tests)
	g++ $(CXXFLAGS) -o run_tests $(objects_tests) googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a -pthread

main: $(objects_main)
	g++ $(CXXFLAGS) -o main $(objects_main)

main.o: main.cpp
	g++ $(CXXFLAGS) -o main.o -c main.cpp

arbre.o : arbre.cpp arbre.h
	g++ $(CXXFLAGS) -c -o arbre.o arbre.cpp	

noeud.o: noeud.cpp noeud.h
	g++ $(CXXFLAGS) -c -o noeud.o noeud.cpp

google_tests.o: google_tests.cpp 
	g++ $(CXXFLAGS) -c google_tests.cpp -o google_tests.o -Igoogletest-release-1.10.0/googletest/include/ -std=c++11 

check:
	./run_tests

clean:
	rm $(objects) 
