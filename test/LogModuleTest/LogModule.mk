include ../../src/base/Log/log.mk

TARGET:=LogMoudleTestDemo
DEMOCPP := LogModuleTest.cpp
DEMOOBJ := $(patsubst %.cpp, %.o, $(DEMOCPP))

LOGSUBDIR:=../../src/base/Log/
THREADSUBDIR := ../../src/base/Thread/
LOGSUBMK:=log.mk
THREADSUBMK:=thread.mk
TIMESUBDIR = ../../src/base/Time/
TIMESUBMK=time.mk
CXXFLAGS := -g -pthread -DDEBUG 				 # -Wall

LOGCPP := $(wildcard ../../src/base/Log/src/*.cpp)
LOGOBJ := $(patsubst %.cpp, %.o, $(LOGCPP))

THREADCPP = $(wildcard ../../src/base/Thread/src/*.cpp)
THREADO = $(patsubst %.cpp, %.o, $(THREADCPP))

TIMECPP = $(wildcard ../../src/base/Time/src/*.cpp)
TIMEOBJ = $(patsubst %.cpp, %.o, $(TIMECPP))

DEPEND += $(THREADO)
DEPEND += $(LOGOBJ)
DEPEND += $(TIMEOBJ)
SOURCECPP += $(THREADCPP)
SOURCECPP += $(LOGCPP)
SOURCECPP += $(TIMECPP)
SOURCECPP += $(DEMOCPP)
DEPEND+=$(DEMOOBJ)

.PYTHON: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCECPP)

$(DEMOOBJ): $(DEMOCPP)

.PYTHON: clean
clean:
	make -C $(LOGSUBDIR) -f $(LOGSUBMK) _clean
	make -C $(THREADSUBDIR) -f $(THREADSUBMK) _clean
	make -C $(TIMESUBDIR) -f $(TIMESUBMK) _clean
	@-$(RM) *.o $(TARGET)
