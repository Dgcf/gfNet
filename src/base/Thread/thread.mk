#vpath %.h ./inc
#vpath %.cpp ./src

CXX=g++
CXXFLAGS=-g -pthread
INCLUDE:=$(wildcard ./inc/*.h)
INCLUDE+= ../../common/common.h
SOURCE:=$(wildcard ./src/*.cpp)

OBJECTS:=$(patsubst %.cpp, %.o, $(SOURCE))

_all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -c $(SOURCE)

.PHONY: _clean
clean:
	@-rm -f ./src/*.o

