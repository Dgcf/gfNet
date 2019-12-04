# !/bin/bash
TARGET:=LogModuleTestDemo
DEMOCPP := LogModuleTest.cpp
DEMOOBJ := $(patsubst %.cpp, %.o, $(DEMOCPP))

LOGSUBDIR:=../../src/base/Log/
LOGSUBMK:=log.mk

THREADSUBDIR := ../../src/base/Thread/
THREADSUBMK:=thread.mk

TIMESUBDIR = ../../src/base/Time/
TIMESUBMK=time.mk

SUBMK = $(join $(LOGSUBDIR), $(LOGSUBMK)) $(join $(THREADSUBDIR), $(THREADSUBMK)) $(join $(TIMESUBDIR), $(TIMESUBMK))

CXXFLAGS := -g -pthread -DDEBUG 				 # -Wall

LOGCPP := $(wildcard $(join $(LOGSUBDIR), src/*.cpp))
LOGOBJ := $(patsubst %.cpp, %.o, $(LOGCPP))

THREADCPP = $(wildcard $(join $(THREADSUBDIR), src/*.cpp))
THREADO = $(patsubst %.cpp, %.o, $(THREADCPP))

TIMECPP = $(wildcard $(join $(TIMESUBDIR), src/*.cpp))
TIMEOBJ = $(patsubst %.cpp, %.o, $(TIMECPP))

SOURCECPP = $(THREADCPP) $(LOGCPP) $(TIMECPP) $(DEMOCPP)
DEPEND =  $(THREADO) $(LOGOBJ) $(TIMEOBJ) $(DEMOOBJ)

.PYTHON: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCECPP)

# 很奇怪，去掉上面一行中的 $(TARGET) 会删掉 thread.cpp 文件

$(DEMOOBJ): $(DEMOCPP)

.PYTHON: clean
clean:
# @echo $(SUBMK)
# for var in a b c d;\
# do\
# 	echo $(var);\
# 	#make -f $(var) _clean
# done
	@make -C $(LOGSUBDIR) -f $(LOGSUBMK) _clean
	@make -C $(THREADSUBDIR) -f $(THREADSUBMK) _clean
	@make -C $(TIMESUBDIR) -f $(TIMESUBMK) _clean
	@-$(RM) *.o $(TARGET)
