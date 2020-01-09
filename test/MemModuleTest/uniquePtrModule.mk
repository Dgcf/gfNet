TARGET = UniquePtrDemo
DEPEND = ../../src/base/Memory/inc/unique_ptr.h
SOURCECPP = ./uniquePtrTest.cpp
CXXFLAGS += -g
SANITIZER := -fsanitize=address 

.PHONY: all
all: $(TARGET)
$(TARGET): $(DEPEND)
	$(CXX) $(CXXFLAGS) $(SANITIZER) -o $@ $(SOURCECPP)

.PHONY: clean
clean:
	@-$(RM) $(TARGET)