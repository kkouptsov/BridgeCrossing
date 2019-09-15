
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
TARGETS=run-tests

COMPILE_FLAGS=-std=c++14 -g -O0
LINK_FLAGS=-L/usr/lib/x86_64-linux-gnu/ -lyaml-cpp

CC=g++


run-tests: $(OBJECTS)
	$(CC) -o run-tests $(OBJECTS) $(LINK_FLAGS)

.cpp.o:
	$(CC) $(COMPILE_FLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
