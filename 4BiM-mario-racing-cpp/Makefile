all: runtests clean

objects = Character.o Mario.o Yoshi.o
CXXFLAGS = -Wall -Wextra -g -std=c++14

runtests: tests
	valgrind ./tests

tests: $(objects) tests.o
	g++ -o $@ $^ googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a -pthread

tests.o: tests.cpp Character.h Mario.h Yoshi.h
	g++ -c $(CXXFLAGS) $< -o $@ -Igoogletest-release-1.10.0/googletest/include/


runmain: main
	valgrind ./main
	make clean

main: main.o $(objects)
	g++ -o $@ $^

main.o: main.cpp Character.h Mario.h Yoshi.h
	g++ -c $(CXXFLAGS) $< -o $@

Character.o: Character.cpp Character.h

Mario.o: Mario.cpp Mario.h Character.h

Yoshi.o: Yoshi.cpp Yoshi.h Character.h

%.o: %.cpp %.h
	g++ -c $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	-$(RM) main tests *.o
