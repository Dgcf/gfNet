objs=ThreadModuleTest.o Condition.o Mutex.o thread.o ThreadPool.o
#VPATH=../src/base/inc:../src/base/src:../src
vpath %.h ../src/base/inc
vpath %.h ../src
vpath %.cpp ../src/base/src

$(var:a=b)
${var:a=b}

.PHONY:all
all: ThreadPoolDemo: $(objs)
	g++ -pthread -Wall -g -o ThreadPoolDemo  $(objs)

ThreadModuleTest.o: blockqueue.h ThreadPool.h
	g++ -g -c ThreadModuleTest.cpp

Condition.o: Condition.h Mutex.h
	g++ -g -c ../src/base/src/Condition.cpp		# vpath在这里不管用

Mutex.o: Mutex.h common.h
	g++ -g -c ../src/base/src/Mutex.cpp

thread.o: thread.h common.h
	g++ -g -c ../src/base/src/thread.cpp

ThreadPool.o: ThreadPool.h thread.h Condition.h common.h
	g++ -g -c ../src/base/src/ThreadPool.cpp

.PHONY: clean
clean:
	@-rm -f *.o ThreadPoolDemo

.PHONY: install
install:

.PHONY: print
print: 

.PHONY: tar
tar:

.PHONY: dist
dist: 

.PHONY: test
test: 