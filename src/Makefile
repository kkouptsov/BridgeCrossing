
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
TARGETS=bridge

COMPILE_FLAGS=-std=c++14 -g -O0
LINK_FLAGS=-L/usr/lib/x86_64-linux-gnu/ -lyaml-cpp

CC=g++


all: $(OBJECTS)
	$(CC) -o run $(OBJECTS) $(LINK_FLAGS)

%: %.cpp
	$(CC) $(COMPILE_FLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
