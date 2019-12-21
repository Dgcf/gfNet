TARGET = SharedPtrDemo
DEPEND = ../../src/base/Memory/inc/shared_ptr.h
SOURCECPP = ./SharedPtrTest.cpp
CXXFLAGS += -g

.PHONY: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCECPP)

.PHONY: clean
clean:
	@-$(RM) $(TARGET)