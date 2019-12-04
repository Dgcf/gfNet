# CXXFLAGS=-g -pthread
# INCLUDE:=$(wildcard ./inc/*.h)
# INCLUDE+= ../../common/common.h
# SOURCE:=$(wildcard ./src/*.cpp)						# 这一行注释了都能编译成功，是什么原因？
# OBJECTS:=$(patsubst ./src/%.cpp, ./src/%.o, $(SOURCE))

#_all: $(OBJECTS)
	#$(CXX) $(CXXFLAGS) -c $(SOURCE)		# 这一行就在thread.mk同一级目录下又生成一遍了

.PHONY: _clean
_clean:
	@-$(RM) ./src/*.o
