include ../../src/base/Log/log.mk

TARGET:=LogMoudleTestDemo
DEMOCPP := LogModuleTest.cpp
DEMOOBJ := $(patsubst %.cpp, %.o, $(DEMOCPP))

SUBDIR:=../../src/base/Log/
SUBMK:=log.mk
CXXFLAGS := -g -pthread -DDEBUG -Wall

LOGCPP := $(wildcard ../../src/base/Log/src/*.cpp)
LOGOBJ := $(patsubst %.cpp, %.o, $(LOGCPP))

THREADCPP = $(wildcard ../../src/base/Thread/src/*.cpp)
THREADO = $(patsubst %.cpp, %.o, $(THREADCPP))

DEPEND += $(THREADO)
DEPEND += $(LOGOBJ)
SOURCECPP += $(THREADCPP)
SOURCECPP += $(LOGCPP)
SOURCECPP += $(DEMOCPP)
DEPEND+=$(DEMOOBJ)

.PYTHON: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	#make -C $(SUBDIR) -f $(SUBMK) _all
	@echo $(DEPEND)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCECPP)

$(DEMOOBJ): $(DEMOCPP)

.PYTHON: clean
clean:
	make -C $(SUBDIR) -f $(SUBMK) _clean
	@-$(RM) *.o $(TARGET)
