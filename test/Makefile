ThreadPoolDemo: ThreadModuleTest.o Condition.o Mutex.o thread.o ThreadPool.o
	g++ -pthread -o ThreadPoolDemo  ThreadModuleTest.o Condition.o Mutex.o thread.o ThreadPool.o 

ThreadModuleTest.o: ../src/base/inc/blockqueue.h ../src/base/inc/ThreadPool.h
	g++ -c ThreadModuleTest.cpp

Condition.o: ../src/base/inc/Condition.h ../src/base/inc/Mutex.h
	g++ -c ../src/base/src/Condition.cpp

Mutex.o: ../src/base/inc/Mutex.h ../src/common.h
	g++ -c ../src/base/src/Mutex.cpp

thread.o: ../src/base/inc/thread.h ../src/common.h
	g++ -c ../src/base/src/thread.cpp

ThreadPool.o: ../src/base/inc/ThreadPool.h ../src/base/inc/thread.h ../src/base/inc/Condition.h ../src/common.h
	g++ -c ../src/base/src/ThreadPool.cpp

clear:
	rm -rf *.o
