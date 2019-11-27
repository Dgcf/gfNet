include ../../src/base/Thread/thread.mk

CXX=g++
TARGET:=ThreadModuleDemo
CPPFILE:=$(wildcard ../../src/base/Thread/src/*.cpp)
DEPEND:=$(patsubst %.cpp, %.o, $(CPPFILE))
CURRENTCPP:=ThreadModuleTest.cpp
SUBDIR:=../../src/base/Thread
SUBMAKEFILE:=thread.mk
LOCAl:=ThreadModuleTest.o
DEPEND+=$(LOCAl)
INCLUDE=$(wildcard ../../src/base/Thread/inc/*.h)

.PHONY: all
all: $(TARGET)
$(TARGET):$(DEPEND)
	cd $(SUBDIR); make -f $(SUBMAKEFILE)
	$(CXX) -g -Wall -pthread -o $(TARGET) $(DEPEND)

$(LOCAl): $(INCLUDE)
	$(CXX) -g -pthread -c $(CURRENTCPP)

.PHONY: clean
clean:
	cd $(SUBDIR); make -f $(SUBMAKEFILE) _clean
	-rm -f $(TARGET) $(LOCAl)