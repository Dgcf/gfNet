SRC := $(wildcard ../../src/net/fnetgt/src/*.cpp)
LOG := $(wildcard ../../src/base/Log/src/*.cpp)
THREAD := $(wildcard ../../src/base/Thread/src/*.cpp)
TIMER := $(wildcard ../../src/base/Time/src/*.cpp)
SRC += $(LOG) $(THREAD) $(TIMER)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEMO := ./Echo_server01.cpp
CXXFLAGS = -g -pthread
TARGET := EchoServer

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEMO) $(SRC) -lrt

.PYTHON:
clean:
	$(RM) $(OBJ) $(TARGET)