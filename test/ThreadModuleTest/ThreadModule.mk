include ../../src/base/Thread/thread.mk

CXX=g++
TARGET:=ThreadModuleDemo
INCLUDE=$(wildcard ../../src/base/Thread/inc/*.h)
CPPFILE:=$(wildcard ../../src/base/Thread/src/*.cpp)
DEPEND:=$(patsubst %.cpp, %.o, $(CPPFILE))
CURRENTCPP:=ThreadModuleTest.cpp
SUBDIR:=../../src/base/Thread
SUBMAKEFILE:=thread.mk
LOCAl:=ThreadModuleTest.o
DEPEND+=$(LOCAl)


.PHONY: all
all: $(TARGET)
$(TARGET):$(DEPEND)
	cd $(SUBDIR); make -f $(SUBMAKEFILE)
	$(CXX) -g -Wall -pthread -o $(TARGET) $(DEPEND)

$(LOCAl): $(INCLUDE)
	$(CXX) -DDEBUG  -g -pthread -c $(CURRENTCPP)

.PHONY: clean
clean:
	cd $(SUBDIR); make -f $(SUBMAKEFILE) _clean
	@-rm -f $(TARGET) $(LOCAl)
