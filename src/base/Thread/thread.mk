CXX=g++
CXXFLAGS=-g -pthread
INCLUDE:=$(wildcard ./inc/*.h)
INCLUDE+= ../../common/common.h
SOURCE:=$(wildcard ./src/*.cpp)

OBJECTS:=$(patsubst %.cpp, %.o, $(SOURCE))

_all: $(OBJECTS)
	#$(CXX) $(CXXFLAGS) -c $(SOURCE)		# 这一行就在thread.mk同一级目录下又生成一遍了

.PHONY: _clean
_clean:
	@-rm -f ./src/*.o
