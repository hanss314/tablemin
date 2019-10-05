CXX=g++
CXXFLAGS=-Wall -I./include
LIBFLAGS=-lhidapi-hidraw -ljack
DEBUGFLAGS=-lasan -pg

MODE=normal

INCLUDE=$(wildcard include/*.h)
SRC=$(wildcard src/*.cc)
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
	rm -rf obj/*

purge:
	make clean
	rm -f $(OUT)
