
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
TARGETS=bridge

CPPFLAGS=-std=c++14 -g -O0

CC=g++


all: $(OBJECTS)
	$(CC) $(CPPFLAGS) -o run $(OBJECTS)

%: %.cpp
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
