
# SOURCE=$(wildcard ./src/*.cpp)
# OBJECT=$(patsubst %.cpp, %.o, $(SOURCE))

# _all: $(OBJECT)
# $(OBJECT): $(SOURCE)

.PHONY: _clean
_clean:
	@-$(RM) ./src/*.o