CXX=g++
CXXFLAGS=-Wall -I./include
LIBFLAGS=-lhidapi-hidraw -pthread -ljack -lX11
DEBUGFLAGS=-p -g -lasan

MODE=normal

INCLUDE=$(wildcard include/*.h)
SRC=$(wildcard src/*.cc) $(wildcard src/profile/*.cc)
OBJ=$(patsubst src/%.cc,obj/%.o,$(SRC))
OUT=tablemin

.PHONY: debug all clean build purge


all: $(OBJ)
ifeq ($(MODE), debug)
	$(CXX) $(LIBFLAGS) $(DEBUGFLAGS) -o $(OUT) $^
else
	$(CXX) $(LIBFLAGS) -o $(OUT) $^
endif

obj/%.o: src/%.cc $(INCLUDE)
ifeq ($(MODE), debug)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $< -o $@
else 
	$(CXX) $(CXXFLAGS) -O3 -c $< -o $@
endif

debug:
	make MODE=debug

clean:
	rm -f obj/**/*.o
	rm -f obj/*.o

purge:
	make clean
	rm $(OUT)
