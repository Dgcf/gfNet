SOURCE=$(wildcard ./src/*.cpp)
OBJECT=$(patsubst ./src/%.cpp, ./src/%.o, $(SOURCE))

_all: $(OBJECT)
$(OBJECT): $(SOURCE)

.PHONY: _clean
_clean:
	@-$(RM) ./src/*.o
