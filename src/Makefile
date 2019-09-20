HEADERS=$(wildcard *.h)
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
DEPS=$(patsubst %.o, %.d, $(OBJECTS))

TARGETS=run-tests

COMPILE_FLAGS=-std=c++14 -g -O0 -Wall
LINK_FLAGS=-L/usr/lib/x86_64-linux-gnu/ -lyaml-cpp

CXX=g++

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LINK_FLAGS)

-include $(DEP)

.cpp.o:
	$(CXX) $(COMPILE_FLAGS) -MMD -c $<

.PHONY: clean
clean:
	rm -f $(TARGETS) $(OBJECTS) $(DEPS)
