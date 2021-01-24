CC = clang++
CFLAGS = -Wall -std=c++11
LDFLAGS = -lSDL2 -lSDL2_image

ifeq ($(DEBUG), yes)
	CFLAGS += -g
else
	CFLAGS += -O3
endif

EXEC = build/main
SRC = $(wildcard src/*.cpp)
OBJ = $(subst src,build,$(SRC:.cpp=.o))

.PHONY: build

build/%.o: src/%.cpp
	@ echo "[building object file $@]"
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ echo "[done]"

$(EXEC): $(OBJ)
	@ echo "[building executable]"
	@ $(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@ echo "[done]"

build:
	@ echo "[creating build dir]"
	@ mkdir -p build/
	@ echo "[done]"

clean:
	rm -f build/*.o

doc: doxyfile
	doxygen doxyfile

mrproper: clean
	rm -f $(EXEC)