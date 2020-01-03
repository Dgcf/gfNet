SRC := $(wildcard ../../src/net/fnetgt/src/*.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEMO := ./Echo_server01.cpp
CXXFLAGS = -g
TARGET := EchoServer

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEMO) $(SRC)

.PYTHON:
clean:
	$(RM) $(OBJ) $(TARGET)