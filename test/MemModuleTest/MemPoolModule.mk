TARGET = MemPoolDemo
DEPEND = ../../src/base/Memory/inc/MemPool.h
SOURCECPP = ./PoolModuleTest.cpp
CXXFLAGS += -g

.PHONY: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCECPP)

.PHONY: clean
clean:
	@-$(RM) $(TARGET)
