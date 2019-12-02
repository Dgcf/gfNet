include ../../src/base/Thread/thread.mk

CXXFLAGS := -g -Wall -pthread
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
	# cd $(SUBDIR); make -f $(SUBMAKEFILE)
	#make -C $(SUBDIR) -f $(SUBMAKEFILE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEPEND)

# $(LOCAl): $(INCLUDE)
# 	$(CXX) -DDEBUG  -g -pthread -c $(CURRENTCPP)
$(LOCAl): $(CURRENTCPP)

.PHONY: clean
clean:
	make -C $(SUBDIR) -f $(SUBMAKEFILE) _clean
	@-$(RM) $(TARGET) $(LOCAl)
